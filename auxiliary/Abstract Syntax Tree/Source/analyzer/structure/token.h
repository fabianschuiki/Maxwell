#pragma once
#include <string>

class StructureNode;


class StructureToken {
public:
	const enum Type {
		Identifier,
		Numeric,
		String,
		
		//Text
		Keyword,
		Symbol,
		
		//Node
		Reference
	} type;
	const std::string text;
	const StructureNode * reference;
	bool safe;
	
	StructureToken(Type type);
	StructureToken(Type type, const std::string & text);
	StructureToken(Type type, StructureNode * reference);
	
	operator std::string ();
};
