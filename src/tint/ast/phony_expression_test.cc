// Copyright 2021 The Tint Authors.
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

#include "src/tint/ast/test_helper.h"

namespace tint {
namespace ast {
namespace {

using IdentifierExpressionTest = TestHelper;

TEST_F(IdentifierExpressionTest, Creation) {
  EXPECT_NE(Phony(), nullptr);
}

TEST_F(IdentifierExpressionTest, Creation_WithSource) {
  auto* p = Phony(Source{{20, 2}});

  auto src = p->source;
  EXPECT_EQ(src.range.begin.line, 20u);
  EXPECT_EQ(src.range.begin.column, 2u);
}

TEST_F(IdentifierExpressionTest, IsPhony) {
  auto* p = Phony();
  EXPECT_TRUE(p->Is<PhonyExpression>());
}

}  // namespace
}  // namespace ast
}  // namespace tint