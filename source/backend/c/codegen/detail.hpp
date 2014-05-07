/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "../CodeGenerator.hpp"
#include "../code.hpp"
#include <ast/nodes/nodes.hpp>
#include <stage/algorithm/type.hpp>
using namespace backendc;
using namespace ast;

#define DEF_ROOT(type) void CodeGenerator::generate##type(const type::Ptr& node)
#define DEF_EXPR(type) void CodeGenerator::generate##type(const type::Ptr& node, ExprCode& out, Context& ctx)
#define DEF_TYPE(type) void CodeGenerator::generate##type(const type::Ptr& node, TypeCode& out)

#define DEF_EXPR_INTF(type) void CodeGenerator::generate##type##Intf(type##Interface* node, ExprCode& out, Context& ctx)
#define DEF_TYPE_INTF(type) void CodeGenerator::generate##type##Intf(type##Interface* node, TypeCode& out)
