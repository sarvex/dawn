// Copyright 2021 The Dawn Authors
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <vector>

#include "dawn/common/Assert.h"
#include "dawn/tests/DawnTest.h"
#include "dawn/utils/ComboRenderPipelineDescriptor.h"
#include "dawn/utils/WGPUHelpers.h"

constexpr static unsigned int kRTSize = 1;

class DepthClippingTest : public DawnTest {
  protected:
    void SetUp() override {
        DawnTest::SetUp();
        DAWN_TEST_UNSUPPORTED_IF(!SupportsFeatures({wgpu::FeatureName::DepthClipControl}));

        wgpu::TextureDescriptor renderTargetDescriptor;
        renderTargetDescriptor.size = {kRTSize, kRTSize};
        renderTargetDescriptor.format = wgpu::TextureFormat::RGBA8Unorm;
        renderTargetDescriptor.usage =
            wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::CopySrc;
        renderTarget = device.CreateTexture(&renderTargetDescriptor);

        renderTargetView = renderTarget.CreateView();

        wgpu::TextureDescriptor depthDescriptor;
        depthDescriptor.dimension = wgpu::TextureDimension::e2D;
        depthDescriptor.size = {kRTSize, kRTSize};
        depthDescriptor.format = wgpu::TextureFormat::Depth24PlusStencil8;
        depthDescriptor.usage = wgpu::TextureUsage::RenderAttachment;
        depthTexture = device.CreateTexture(&depthDescriptor);

        depthTextureView = depthTexture.CreateView();

        vsModule = utils::CreateShaderModule(device, R"(
            struct UBO {
                color : vec3f,
                depth : f32,
            }
            @group(0) @binding(0) var<uniform> ubo : UBO;

            @vertex fn main() -> @builtin(position) vec4f {
                return vec4f(0.0, 0.0, ubo.depth, 1.0);
            })");

        fsModule = utils::CreateShaderModule(device, R"(
            struct UBO {
                color : vec3f,
                depth : f32,
            }
            @group(0) @binding(0) var<uniform> ubo : UBO;

            @fragment fn main() -> @location(0) vec4f {
                return vec4f(ubo.color, 1.0);
            })");
    }

    std::vector<wgpu::FeatureName> GetRequiredFeatures() override {
        std::vector<wgpu::FeatureName> requiredFeatures = {};
        if (SupportsFeatures({wgpu::FeatureName::DepthClipControl})) {
            requiredFeatures.push_back(wgpu::FeatureName::DepthClipControl);
        }
        return requiredFeatures;
    }

    struct TestSpec {
        wgpu::PrimitiveDepthClipControl* depthClipControl;
        utils::RGBA8 color;
        float depth;
    };

    // Each test param represents a pair of triangles with a color, depth, stencil value, and
    // depthStencil state, one frontfacing, one backfacing Draw the triangles in order and check the
    // expected colors for the frontfaces and backfaces
    void DoTest(const std::vector<TestSpec>& testParams, const utils::RGBA8& expected) {
        wgpu::CommandEncoder encoder = device.CreateCommandEncoder();

        struct TriangleData {
            float color[3];
            float depth;
        };

        utils::ComboRenderPassDescriptor renderPass({renderTargetView}, depthTextureView);
        wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&renderPass);

        for (size_t i = 0; i < testParams.size(); ++i) {
            const TestSpec& test = testParams[i];

            TriangleData data = {
                {static_cast<float>(test.color.r) / 255.f, static_cast<float>(test.color.g) / 255.f,
                 static_cast<float>(test.color.b) / 255.f},
                test.depth,
            };
            // Upload a buffer for each triangle's depth and color data
            wgpu::Buffer buffer = utils::CreateBufferFromData(device, &data, sizeof(TriangleData),
                                                              wgpu::BufferUsage::Uniform);

            // Create a pipeline for the triangles with the test spec's params.
            utils::ComboRenderPipelineDescriptor descriptor;
            descriptor.primitive.nextInChain = test.depthClipControl;
            descriptor.primitive.topology = wgpu::PrimitiveTopology::PointList;
            descriptor.vertex.module = vsModule;
            descriptor.cFragment.module = fsModule;
            wgpu::DepthStencilState* depthStencil = descriptor.EnableDepthStencil();
            depthStencil->depthWriteEnabled = true;
            depthStencil->format = wgpu::TextureFormat::Depth24PlusStencil8;

            wgpu::RenderPipeline pipeline = device.CreateRenderPipeline(&descriptor);

            // Create a bind group for the data
            wgpu::BindGroup bindGroup =
                utils::MakeBindGroup(device, pipeline.GetBindGroupLayout(0), {{0, buffer}});

            pass.SetPipeline(pipeline);
            pass.SetBindGroup(0, bindGroup);
            pass.Draw(1);
        }
        pass.End();

        wgpu::CommandBuffer commands = encoder.Finish();
        queue.Submit(1, &commands);

        EXPECT_PIXEL_RGBA8_EQ(expected, renderTarget, 0, 0) << "Pixel check failed";
    }

    wgpu::Texture renderTarget;
    wgpu::Texture depthTexture;
    wgpu::TextureView renderTargetView;
    wgpu::TextureView depthTextureView;
    wgpu::ShaderModule vsModule;
    wgpu::ShaderModule fsModule;
};

// Test that fragments beyond the far plane are not clipped if unclippedDepth is true
TEST_P(DepthClippingTest, UnclippedBeyondFarPlane) {
    wgpu::PrimitiveDepthClipControl depthClipControl;
    depthClipControl.unclippedDepth = true;

    DoTest(
        {
            // Draw a red triangle at depth 1.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(255, 0, 0, 255), /* color */
                1.f,                          /* depth */
            },
            // Draw a green triangle at depth 2 which should not be clipped.
            {
                &depthClipControl,            /* depthClipControl */
                utils::RGBA8(0, 255, 0, 255), /* color */
                2.f,                          /* depth */
            },
        },
        // The resulting fragment should be green even though the green triangle is
        // outside the clip volume.
        utils::RGBA8(0, 255, 0, 255));
}

// Test that fragments beyond the far plane are clipped if unclippedDepth is false
TEST_P(DepthClippingTest, ClippedBeyondFarPlane) {
    wgpu::PrimitiveDepthClipControl depthClipControl;
    depthClipControl.unclippedDepth = false;

    DoTest(
        {
            // Draw a red triangle at depth 1.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(255, 0, 0, 255), /* color */
                1.f,                          /* depth */
            },
            // Draw a green triangle at depth 2 which should be clipped.
            {
                &depthClipControl,            /* depthClipControl */
                utils::RGBA8(0, 255, 0, 255), /* color */
                2.f,                          /* depth */
            },
        },
        // The resulting fragment should be red since the green triangle is
        // outside the clip volume.
        utils::RGBA8(255, 0, 0, 255));
}

// Test that fragments beyond the far plane are clipped if unclippedDepth is not specified
TEST_P(DepthClippingTest, ClippedBeyondFarPlaneFeatureUnused) {
    DoTest(
        {
            // Draw a red triangle at depth 1.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(255, 0, 0, 255), /* color */
                1.f,                          /* depth */
            },
            // Draw a green triangle at depth 2 which should be clipped.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(0, 255, 0, 255), /* color */
                2.f,                          /* depth */
            },
        },
        // The resulting fragment should be red since the green triangle is
        // outside the clip volume.
        utils::RGBA8(255, 0, 0, 255));
}

// Test that fragments beyond the near plane are not clipped if unclippedDepth is true
TEST_P(DepthClippingTest, UnclippedBeyondNearPlane) {
    wgpu::PrimitiveDepthClipControl depthClipControl;
    depthClipControl.unclippedDepth = true;

    DoTest(
        {
            // Draw a red triangle at depth 0.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(255, 0, 0, 255), /* color */
                0.f,                          /* depth */
            },
            // Draw a green triangle at depth -1 which should not be clipped.
            {
                &depthClipControl,            /* depthClipControl */
                utils::RGBA8(0, 255, 0, 255), /* color */
                -1.f,                         /* depth */
            },
        },
        // The resulting fragment should be green even though the green triangle is
        // outside the clip volume.
        utils::RGBA8(0, 255, 0, 255));
}

// Test that fragments beyond the near plane are clipped if unclippedDepth is false
TEST_P(DepthClippingTest, ClippedBeyondNearPlane) {
    wgpu::PrimitiveDepthClipControl depthClipControl;
    depthClipControl.unclippedDepth = false;

    DoTest(
        {
            // Draw a red triangle at depth 0.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(255, 0, 0, 255), /* color */
                0.f,                          /* depth */
            },
            // Draw a green triangle at depth -1 which should be clipped.
            {
                &depthClipControl,            /* depthClipControl */
                utils::RGBA8(0, 255, 0, 255), /* color */
                -1.f,                         /* depth */
            },
        },
        // The resulting fragment should be red because the green triangle is
        // outside the clip volume.
        utils::RGBA8(255, 0, 0, 255));
}

// Test that fragments beyond the near plane are clipped if unclippedDepth is not specified
TEST_P(DepthClippingTest, ClippedBeyondNearPlaneFeatureUnused) {
    DoTest(
        {
            // Draw a red triangle at depth 0.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(255, 0, 0, 255), /* color */
                0.f,                          /* depth */
            },
            // Draw a green triangle at depth -1 which should be clipped.
            {
                nullptr,                      /* depthClipControl */
                utils::RGBA8(0, 255, 0, 255), /* color */
                -1.f,                         /* depth */
            },
        },
        // The resulting fragment should be red because the green triangle is
        // outside the clip volume.
        utils::RGBA8(255, 0, 0, 255));
}

// Test that fragments are properly clipped or clamped if multiple render pipelines are used
// within the same render pass with differing unclippedDepth values.
TEST_P(DepthClippingTest, MultipleRenderPipelines) {
    wgpu::PrimitiveDepthClipControl depthClipControl1;
    depthClipControl1.unclippedDepth = true;

    wgpu::PrimitiveDepthClipControl depthClipControl2;
    depthClipControl2.unclippedDepth = false;

    DoTest(
        {
            // Draw green with no clipping
            {
                &depthClipControl1, utils::RGBA8(0, 255, 0, 255), /* color */
                2.f,                                              /* depth */
            },
            // Draw red with clipping
            {
                &depthClipControl2, utils::RGBA8(255, 0, 0, 255), /* color */
                2.f,                                              /* depth */
            },
        },
        utils::RGBA8(0, 255, 0, 255));  // Result should be green
}

// Test that fragments are not clipped if unclippedDepth is true and that their
// depths are not being clamped instead. In the fragment shader, we should see
// depth values outside the viewport.
TEST_P(DepthClippingTest, UnclippedNotClamped) {
    wgpu::PrimitiveDepthClipControl depthClipControl;
    depthClipControl.unclippedDepth = true;

    // Create a pipeline to render a point.
    utils::ComboRenderPipelineDescriptor descriptor;
    descriptor.primitive.nextInChain = &depthClipControl;
    descriptor.primitive.topology = wgpu::PrimitiveTopology::PointList;
    // Draw the point at (0, 0) with depth 2.0.
    descriptor.vertex.module = utils::CreateShaderModule(device, R"(
        @vertex fn main() -> @builtin(position) vec4f {
            return vec4f(0.0, 0.0, 2.0, 1.0);
        })");
    // Write frag_pos.z / 4.0 which should be about 0.5 to the red channel.
    // This is the depth output from the vertex shader which is not clamped to the viewport.
    descriptor.cFragment.module = utils::CreateShaderModule(device, R"(
        @fragment fn main(@builtin(position) frag_pos: vec4f) -> @location(0) vec4f {
            return vec4f(frag_pos.z / 4.0, 0.0, 0.0, 1.0);
        })");
    wgpu::DepthStencilState* depthStencil = descriptor.EnableDepthStencil();
    depthStencil->depthWriteEnabled = true;
    depthStencil->format = wgpu::TextureFormat::Depth24PlusStencil8;

    wgpu::RenderPipeline pipeline = device.CreateRenderPipeline(&descriptor);

    // Draw the point.
    wgpu::CommandEncoder encoder = device.CreateCommandEncoder();
    utils::ComboRenderPassDescriptor renderPass({renderTargetView}, depthTextureView);
    wgpu::RenderPassEncoder pass = encoder.BeginRenderPass(&renderPass);
    pass.SetPipeline(pipeline);
    pass.Draw(1);
    pass.End();
    wgpu::CommandBuffer commands = encoder.Finish();
    queue.Submit(1, &commands);

    EXPECT_PIXEL_RGBA8_BETWEEN(utils::RGBA8(127, 0, 0, 255), utils::RGBA8(128, 0, 0, 255),
                               renderTarget, 0, 0)
        << "Pixel check failed";
}

DAWN_INSTANTIATE_TEST(DepthClippingTest,
                      D3D11Backend(),
                      D3D12Backend(),
                      MetalBackend(),
                      OpenGLBackend(),
                      OpenGLESBackend(),
                      VulkanBackend());
