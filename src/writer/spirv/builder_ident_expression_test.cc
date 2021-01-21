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

#include <memory>

#include "gtest/gtest.h"
#include "src/ast/binary_expression.h"
#include "src/ast/float_literal.h"
#include "src/ast/identifier_expression.h"
#include "src/ast/scalar_constructor_expression.h"
#include "src/ast/sint_literal.h"
#include "src/ast/type_constructor_expression.h"
#include "src/ast/variable.h"
#include "src/type/f32_type.h"
#include "src/type/i32_type.h"
#include "src/type/vector_type.h"
#include "src/type_determiner.h"
#include "src/writer/spirv/builder.h"
#include "src/writer/spirv/spv_dump.h"
#include "src/writer/spirv/test_helper.h"

namespace tint {
namespace writer {
namespace spirv {
namespace {

using BuilderTest = TestHelper;

TEST_F(BuilderTest, IdentifierExpression_GlobalConst) {
  auto* init = vec3<f32>(1.f, 1.f, 3.f);
  EXPECT_TRUE(td.DetermineResultType(init)) << td.error();

  auto* v = Const("var", ast::StorageClass::kOutput, ty.f32, init,
                  ast::VariableDecorationList{});
  td.RegisterVariableForTesting(v);

  auto* expr = Expr("var");
  ASSERT_TRUE(td.DetermineResultType(expr));

  spirv::Builder& b = Build();

  EXPECT_TRUE(b.GenerateGlobalVariable(v)) << b.error();
  ASSERT_FALSE(b.has_error()) << b.error();

  EXPECT_EQ(DumpInstructions(b.types()), R"(%2 = OpTypeFloat 32
%1 = OpTypeVector %2 3
%3 = OpConstant %2 1
%4 = OpConstant %2 3
%5 = OpConstantComposite %1 %3 %3 %4
)");

  EXPECT_EQ(b.GenerateIdentifierExpression(expr), 5u);
}

TEST_F(BuilderTest, IdentifierExpression_GlobalVar) {
  auto* v = Var("var", ast::StorageClass::kOutput, ty.f32);
  td.RegisterVariableForTesting(v);

  auto* expr = Expr("var");
  ASSERT_TRUE(td.DetermineResultType(expr));

  spirv::Builder& b = Build();

  b.push_function(Function{});
  EXPECT_TRUE(b.GenerateGlobalVariable(v)) << b.error();
  EXPECT_EQ(DumpInstructions(b.debug()), R"(OpName %1 "var"
)");
  EXPECT_EQ(DumpInstructions(b.types()), R"(%3 = OpTypeFloat 32
%2 = OpTypePointer Output %3
%4 = OpConstantNull %3
%1 = OpVariable %2 Output %4
)");

  EXPECT_EQ(b.GenerateIdentifierExpression(expr), 1u);
}

TEST_F(BuilderTest, IdentifierExpression_FunctionConst) {
  auto* init = vec3<f32>(1.f, 1.f, 3.f);
  EXPECT_TRUE(td.DetermineResultType(init)) << td.error();

  auto* v = Const("var", ast::StorageClass::kOutput, ty.f32, init,
                  ast::VariableDecorationList{});
  td.RegisterVariableForTesting(v);

  auto* expr = Expr("var");
  ASSERT_TRUE(td.DetermineResultType(expr));

  spirv::Builder& b = Build();

  EXPECT_TRUE(b.GenerateFunctionVariable(v)) << b.error();
  ASSERT_FALSE(b.has_error()) << b.error();

  EXPECT_EQ(DumpInstructions(b.types()), R"(%2 = OpTypeFloat 32
%1 = OpTypeVector %2 3
%3 = OpConstant %2 1
%4 = OpConstant %2 3
%5 = OpConstantComposite %1 %3 %3 %4
)");

  EXPECT_EQ(b.GenerateIdentifierExpression(expr), 5u);
}

TEST_F(BuilderTest, IdentifierExpression_FunctionVar) {
  auto* v = Var("var", ast::StorageClass::kNone, ty.f32);
  td.RegisterVariableForTesting(v);

  auto* expr = Expr("var");
  ASSERT_TRUE(td.DetermineResultType(expr));

  spirv::Builder& b = Build();

  b.push_function(Function{});
  EXPECT_TRUE(b.GenerateFunctionVariable(v)) << b.error();
  EXPECT_EQ(DumpInstructions(b.debug()), R"(OpName %1 "var"
)");
  EXPECT_EQ(DumpInstructions(b.types()), R"(%3 = OpTypeFloat 32
%2 = OpTypePointer Function %3
%4 = OpConstantNull %3
)");

  const auto& func = b.functions()[0];
  EXPECT_EQ(DumpInstructions(func.variables()),
            R"(%1 = OpVariable %2 Function %4
)");

  EXPECT_EQ(b.GenerateIdentifierExpression(expr), 1u);
}

TEST_F(BuilderTest, IdentifierExpression_Load) {
  auto* var = Var("var", ast::StorageClass::kPrivate, ty.i32);
  td.RegisterVariableForTesting(var);

  auto* expr = Add("var", "var");
  ASSERT_TRUE(td.DetermineResultType(expr)) << td.error();

  spirv::Builder& b = Build();

  b.push_function(Function{});
  ASSERT_TRUE(b.GenerateGlobalVariable(var)) << b.error();

  EXPECT_EQ(b.GenerateBinaryExpression(expr->As<ast::BinaryExpression>()), 7u)
      << b.error();
  EXPECT_EQ(DumpInstructions(b.types()), R"(%3 = OpTypeInt 32 1
%2 = OpTypePointer Private %3
%4 = OpConstantNull %3
%1 = OpVariable %2 Private %4
)");
  EXPECT_EQ(DumpInstructions(b.functions()[0].instructions()),
            R"(%5 = OpLoad %3 %1
%6 = OpLoad %3 %1
%7 = OpIAdd %3 %5 %6
)");
}

TEST_F(BuilderTest, IdentifierExpression_NoLoadConst) {
  auto* var = Const("var", ast::StorageClass::kNone, ty.i32, Expr(2),
                    ast::VariableDecorationList{});
  td.RegisterVariableForTesting(var);

  auto* expr = Add("var", "var");
  ASSERT_TRUE(td.DetermineResultType(expr)) << td.error();

  spirv::Builder& b = Build();

  b.push_function(Function{});
  ASSERT_TRUE(b.GenerateGlobalVariable(var)) << b.error();

  EXPECT_EQ(b.GenerateBinaryExpression(expr->As<ast::BinaryExpression>()), 3u)
      << b.error();
  EXPECT_EQ(DumpInstructions(b.types()), R"(%1 = OpTypeInt 32 1
%2 = OpConstant %1 2
)");
  EXPECT_EQ(DumpInstructions(b.functions()[0].instructions()),
            R"(%3 = OpIAdd %1 %2 %2
)");
}

}  // namespace
}  // namespace spirv
}  // namespace writer
}  // namespace tint
