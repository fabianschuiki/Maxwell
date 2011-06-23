#pragma once
#include <string>
#include <vector>
#include "token.h"


class StructureNode {
public:
	typedef std::vector<StructureToken *> Tokens;
	typedef std::vector<Tokens> Branches;
	
private:
	const std::string name;
	Branches branches;
	
public:
	StructureNode(const std::string & name);
	~StructureNode();
	
	const std::string & getName() const;
	const Branches & getBranches() const;
	
	StructureNode & fork();
	StructureNode & add(StructureToken * node);
	
	operator std::string ();
};
