// Copyright 2023 The Dawn Authors
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

#ifndef INCLUDE_DAWN_NATIVE_D3DBACKEND_H_
#define INCLUDE_DAWN_NATIVE_D3DBACKEND_H_

#include <dxgi1_4.h>
#include <windows.h>
#include <wrl/client.h>

#include "dawn/native/DawnNative.h"

namespace dawn::native::d3d {

struct DAWN_NATIVE_EXPORT AdapterDiscoveryOptions : public AdapterDiscoveryOptionsBase {
    AdapterDiscoveryOptions(WGPUBackendType type, Microsoft::WRL::ComPtr<IDXGIAdapter> adapter);
    Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
};

}  // namespace dawn::native::d3d

#endif  // INCLUDE_DAWN_NATIVE_D3DBACKEND_H_
