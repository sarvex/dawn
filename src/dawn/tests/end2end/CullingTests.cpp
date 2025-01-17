// Copyright 2019 The Dawn Authors
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

#include "dawn/tests/DawnTest.h"

#include "dawn/utils/ComboRenderPipelineDescriptor.h"
#include "dawn/utils/WGPUHelpers.h"

class CullingTest : public DawnTest {
  protected:
    wgpu::RenderPipeline CreatePipelineForTest(wgpu::FrontFace frontFace, wgpu::CullMode cullMode) {
        utils::ComboRenderPipelineDescriptor pipelineDescriptor;

        // Draw two triangles with different winding orders:
        // 1. The top-left one is counterclockwise (CCW)
        // 2. The bottom-right one is clockwise (CW)
        pipelineDescriptor.vertex.module = utils::CreateShaderModule(device, R"(
            @vertex
            fn main(@builtin(vertex_index) VertexIndex : u32) -> @builtin(position) vec4f {
                var pos = array(
                    vec2f(-1.0,  1.0),
                    vec2f(-1.0,  0.0),
                    vec2f( 0.0,  1.0),
                    vec2f( 0.0, -1.0),
                    vec2f( 1.0,  0.0),
                    vec2f( 1.0, -1.0));
                return vec4f(pos[VertexIndex], 0.0, 1.0);
            })");

        // FragCoord of pixel(x, y) in framebuffer coordinate is (x + 0.5, y + 0.5). And we use
        // RGBA8 format for the back buffer. So (FragCoord.xy - vec2(0.5)) / 255 in shader code
        // will make the pixel's R and G channels exactly equal to the pixel's x and y coordinates.
        pipelineDescriptor.cFragment.module = utils::CreateShaderModule(device, R"(
            @fragment
            fn main(@builtin(position) FragCoord : vec4f) -> @location(0) vec4f {
                return vec4f(
                    (FragCoord.xy - vec2f(0.5, 0.5)) / vec2f(255.0, 255.0),
                    0.0, 1.0);
            })");

        // Set culling mode and front face according to the parameters
        pipelineDescriptor.primitive.frontFace = frontFace;
        pipelineDescriptor.primitive.cullMode = cullMode;

        return device.CreateRenderPipeline(&pipelineDescriptor);
    }

    wgpu::Texture Create2DTextureForTest(wgpu::TextureFormat format) {
        wgpu::TextureDescriptor textureDescriptor;
        textureDescriptor.dimension = wgpu::TextureDimension::e2D;
        textureDescriptor.format = format;
        textureDescriptor.usage =
            wgpu::TextureUsage::RenderAttachment | wgpu::TextureUsage::CopySrc;
        textureDescriptor.mipLevelCount = 1;
        textureDescriptor.sampleCount = 1;
        textureDescriptor.size = {kSize, kSize, 1};
        return device.CreateTexture(&textureDescriptor);
    }

    void DoTest(wgpu::FrontFace frontFace,
                wgpu::CullMode cullMode,
                bool isCCWTriangleCulled,
                bool isCWTriangleCulled) {
        wgpu::Texture colorTexture = Create2DTextureForTest(wgpu::TextureFormat::RGBA8Unorm);

        utils::ComboRenderPassDescriptor renderPassDescriptor({colorTexture.CreateView()});
        renderPassDescriptor.cColorAttachments[0].clearValue = {0.0, 0.0, 1.0, 1.0};
        renderPassDescriptor.cColorAttachments[0].loadOp = wgpu::LoadOp::Clear;

        wgpu::CommandEncoder commandEncoder = device.CreateCommandEncoder();
        wgpu::RenderPassEncoder renderPass = commandEncoder.BeginRenderPass(&renderPassDescriptor);
        renderPass.SetPipeline(CreatePipelineForTest(frontFace, cullMode));
        renderPass.Draw(6);
        renderPass.End();
        wgpu::CommandBuffer commandBuffer = commandEncoder.Finish();
        queue.Submit(1, &commandBuffer);

        const utils::RGBA8 kBackgroundColor = utils::RGBA8::kBlue;
        const utils::RGBA8 kTopLeftColor = utils::RGBA8::kBlack;
        constexpr utils::RGBA8 kBottomRightColor = utils::RGBA8(3, 3, 0, 255);

        utils::RGBA8 kCCWTriangleTopLeftColor =
            isCCWTriangleCulled ? kBackgroundColor : kTopLeftColor;
        EXPECT_PIXEL_RGBA8_EQ(kCCWTriangleTopLeftColor, colorTexture, 0, 0);

        utils::RGBA8 kCWTriangleBottomRightColor =
            isCWTriangleCulled ? kBackgroundColor : kBottomRightColor;
        EXPECT_PIXEL_RGBA8_EQ(kCWTriangleBottomRightColor, colorTexture, kSize - 1, kSize - 1);
    }

    static constexpr uint32_t kSize = 4;
};

TEST_P(CullingTest, CullNoneWhenCCWIsFrontFace) {
    DoTest(wgpu::FrontFace::CCW, wgpu::CullMode::None, false, false);
}

TEST_P(CullingTest, CullFrontFaceWhenCCWIsFrontFace) {
    DoTest(wgpu::FrontFace::CCW, wgpu::CullMode::Front, true, false);
}

TEST_P(CullingTest, CullBackFaceWhenCCWIsFrontFace) {
    DoTest(wgpu::FrontFace::CCW, wgpu::CullMode::Back, false, true);
}

TEST_P(CullingTest, CullNoneWhenCWIsFrontFace) {
    DoTest(wgpu::FrontFace::CW, wgpu::CullMode::None, false, false);
}

TEST_P(CullingTest, CullFrontFaceWhenCWIsFrontFace) {
    DoTest(wgpu::FrontFace::CW, wgpu::CullMode::Front, false, true);
}

TEST_P(CullingTest, CullBackFaceWhenCWIsFrontFace) {
    DoTest(wgpu::FrontFace::CW, wgpu::CullMode::Back, true, false);
}

DAWN_INSTANTIATE_TEST(CullingTest,
                      D3D11Backend(),
                      D3D12Backend(),
                      MetalBackend(),
                      OpenGLBackend(),
                      OpenGLESBackend(),
                      VulkanBackend());
