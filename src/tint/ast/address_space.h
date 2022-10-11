// Copyright 2022 The Tint Authors.
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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/ast/address_space.h.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#ifndef SRC_TINT_AST_ADDRESS_SPACE_H_
#define SRC_TINT_AST_ADDRESS_SPACE_H_

#include <ostream>

namespace tint::ast {

/// Address space of a given pointer.
enum class AddressSpace {
    kInvalid,
    kFunction,
    kHandle,  // Tint-internal enum entry - not parsed
    kIn,      // Tint-internal enum entry - not parsed
    kNone,    // Tint-internal enum entry - not parsed
    kOut,     // Tint-internal enum entry - not parsed
    kPrivate,
    kPushConstant,
    kStorage,
    kUniform,
    kWorkgroup,
};

/// @param out the std::ostream to write to
/// @param value the AddressSpace
/// @returns `out` so calls can be chained
std::ostream& operator<<(std::ostream& out, AddressSpace value);

/// ParseAddressSpace parses a AddressSpace from a string.
/// @param str the string to parse
/// @returns the parsed enum, or AddressSpace::kInvalid if the string could not be parsed.
AddressSpace ParseAddressSpace(std::string_view str);

constexpr const char* kAddressSpaceStrings[] = {
    "function", "private", "push_constant", "storage", "uniform", "workgroup",
};

/// @returns true if the AddressSpace is host-shareable
/// @param address_space the AddressSpace
/// @see https://gpuweb.github.io/gpuweb/wgsl.html#host-shareable
inline bool IsHostShareable(AddressSpace address_space) {
    return address_space == ast::AddressSpace::kUniform ||
           address_space == ast::AddressSpace::kStorage ||
           address_space == ast::AddressSpace::kPushConstant;
}

}  // namespace tint::ast

#endif  // SRC_TINT_AST_ADDRESS_SPACE_H_
