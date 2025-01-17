// Copyright 2017 The Dawn Authors
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

#ifndef SRC_DAWN_SAMPLES_SAMPLEUTILS_H_
#define SRC_DAWN_SAMPLES_SAMPLEUTILS_H_

#include "dawn/webgpu_cpp.h"

bool InitSample(int argc, const char** argv);
void DoFlush();
bool ShouldQuit();

struct GLFWwindow;
struct GLFWwindow* GetGLFWWindow();

wgpu::Device CreateCppDawnDevice();
wgpu::TextureFormat GetPreferredSwapChainTextureFormat();
wgpu::SwapChain GetSwapChain();
wgpu::TextureView CreateDefaultDepthStencilView(const wgpu::Device& device);

#endif  // SRC_DAWN_SAMPLES_SAMPLEUTILS_H_
