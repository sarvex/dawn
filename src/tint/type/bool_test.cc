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

#include "src/tint/type/test_helper.h"
#include "src/tint/type/texture.h"

namespace tint::type {
namespace {

using BoolTest = TestHelper;

TEST_F(BoolTest, Creation) {
    auto* a = create<Bool>();
    auto* b = create<Bool>();
    EXPECT_EQ(a, b);
}

TEST_F(BoolTest, Hash) {
    auto* a = create<Bool>();
    auto* b = create<Bool>();
    EXPECT_EQ(a->unique_hash, b->unique_hash);
}

TEST_F(BoolTest, Equals) {
    auto* a = create<Bool>();
    auto* b = create<Bool>();
    EXPECT_TRUE(a->Equals(*b));
    EXPECT_FALSE(a->Equals(Void{}));
}

TEST_F(BoolTest, FriendlyName) {
    Bool b;
    EXPECT_EQ(b.FriendlyName(Symbols()), "bool");
}

TEST_F(BoolTest, Clone) {
    auto* a = create<Bool>();
    type::Manager mgr;
    type::CloneContext ctx{{nullptr}, {nullptr, &mgr}};

    auto* b = a->Clone(ctx);
    ASSERT_TRUE(b->Is<Bool>());
}

}  // namespace
}  // namespace tint::type
