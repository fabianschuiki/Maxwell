#pragma once
#include <map>
#include <stack>
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
	
	std::stack<int> branchStack;
	std::map<int, int> branchLocations;
	
public:
	StructureNode(const std::string & name);
	~StructureNode();
	
	const std::string & getName() const;
	const Branches & getBranches() const;
	
	int getBranchLocation(int token);
	
	StructureNode & fork();
	StructureNode & add(StructureToken * token);
	StructureNode & safe();
	StructureNode & many();
	StructureNode & opt();
	StructureNode & done();
	
	operator std::string ();
};