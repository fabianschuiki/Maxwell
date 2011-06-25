#pragma once
#include <string>

class StructureNode;


class StructureToken {
public:
	const enum Type {
		Empty,
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
	StructureNode * const reference;
	bool safe;
	enum Group {
		None,
		Done,
		Optional,
		Many
	} group;
	
	StructureToken(Type type);
	StructureToken(Type type, const std::string & text);
	StructureToken(Type type, StructureNode * reference);
	void init();
	
	bool dontMatch() const;
	
	operator std::string ();
};
