// Copyright 2020 The Tint Authors.
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

#include "src/ast/module.h"

#include <sstream>

namespace tint {
namespace ast {

const Import* Module::FindImportByName(const std::string& name) {
  for (const auto& import : imports_) {
    if (import->name() == name)
      return import.get();
  }
  return nullptr;
}

bool Module::IsValid() const {
  for (const auto& import : imports_) {
    if (import == nullptr || !import->IsValid()) {
      return false;
    }
  }
  for (const auto& var : global_variables_) {
    if (var == nullptr || !var->IsValid()) {
      return false;
    }
  }
  for (const auto& ep : entry_points_) {
    if (ep == nullptr || !ep->IsValid()) {
      return false;
    }
  }
  for (const auto& alias : alias_types_) {
    if (alias == nullptr) {
      return false;
    }
  }
  for (const auto& func : functions_) {
    if (func == nullptr || !func->IsValid()) {
      return false;
    }
  }
  return true;
}

std::string Module::to_str() const {
  std::ostringstream out;

  for (const auto& import : imports_) {
    import->to_str(out, 0);
  }
  for (const auto& var : global_variables_) {
    var->to_str(out, 0);
  }
  for (const auto& ep : entry_points_) {
    ep->to_str(out, 0);
  }
  for (const auto& alias : alias_types_) {
    out << alias->name() << " -> " << alias->type()->type_name() << std::endl;
  }
  for (const auto& func : functions_) {
    func->to_str(out, 0);
  }

  return out.str();
}

}  // namespace ast
}  // namespace tint
