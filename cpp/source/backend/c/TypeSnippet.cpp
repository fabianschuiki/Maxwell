/* Copyright (c) 2014 Fabian Schuiki */
#include "TypeSnippet.hpp"
#include <stage/algorithm/type.hpp>

using namespace backendc;
using ast::NodePtr;


/** Returns a pointer to the TypeSnippet stored in the table for the given
 * type, or NULL if no such entry is found. */
const TypeSnippet* TypeSnippetTable::find(const NodePtr& type) const
{
	if (!type) return NULL;
	SnippetTable::const_iterator i = table.find(type->describe());
	if (i != table.end()) {
		const SnippetVector& v = i->second;
		for (SnippetVector::const_iterator k = v.begin(); k != v.end(); k++)
			if (stage::algorithm::type::equal(k->type, type))
				return &*k;
	}
	return NULL;
}

void TypeSnippetTable::add(const TypeSnippet& snippet)
{
	table[snippet.type->describe()].push_back(snippet);
}

void TypeSnippetTable::clear()
{
	table.clear();
}

bool TypeSnippetTable::empty()
{
	return table.empty();
}
