/* Copyright (c) 2014 Fabian Schuiki */
#pragma once
#include <ast/Node.hpp>
#include <map>
#include <string>
#include <vector>

namespace backendc {

struct TypeSnippet
{
	ast::NodePtr type;
	std::string def;
	std::string decl;
	std::string ref;
};

class TypeSnippetTable
{
public:
	const TypeSnippet* find(const ast::NodePtr& type) const;
	void add(const TypeSnippet& snippet);
	void clear();
	bool empty();

private:
	typedef std::vector<TypeSnippet> SnippetVector;
	typedef std::map<std::string, SnippetVector> SnippetTable;
	SnippetTable table;
};

} // namespace backendc
