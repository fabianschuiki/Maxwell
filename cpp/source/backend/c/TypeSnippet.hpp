/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <stage/algorithm/type.hpp>
#include <string>

namespace backendc {

struct TypeSnippet
{
	std::string def;
	std::string decl;
	std::string ref;
};

struct TypeRef
{
	ast::NodePtr ptr;
	TypeRef(const ast::NodePtr &p): ptr(p) {}
	bool operator< (const TypeRef &t) const { return stage::algorithm::type::compare(ptr, t.ptr) < 0; }
};

} // namespace backendc
