/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include "../CodeGen2.hpp"
#include "../code.hpp"
#include <ast/nodes/nodes.hpp>
#include <stage/algorithm/type.hpp>
using namespace backendc;
using namespace ast;

#define DEF_ROOT(type) void CodeGen2::generate##type(const type::Ptr& node)
#define DEF_EXPR(type) void CodeGen2::generate##type(const type::Ptr& node, ExprCode& out, Context& ctx)
#define DEF_TYPE(type) void CodeGen2::generate##type(const type::Ptr& node, TypeCode& out)

#define DEF_EXPR_INTF(type) void CodeGen2::generate##type##Intf(type##Interface* node, ExprCode& out, Context& ctx)
#define DEF_TYPE_INTF(type) void CodeGen2::generate##type##Intf(type##Interface* node, TypeCode& out)
