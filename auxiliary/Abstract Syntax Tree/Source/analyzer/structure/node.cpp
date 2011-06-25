#include <assert.h>
#include <sstream>
#include "node.h"


StructureNode::StructureNode(const std::string & n) : name(n)
{
}

StructureNode::~StructureNode()
{
	//Delete all nodes and clear the branches.
	for (Branches::iterator b = branches.begin(); b != branches.end(); b++)
		for (Tokens::iterator t = (*b).begin(); t != (*b).end(); t++)
			delete (*t);
	branches.clear();
}



const std::string & StructureNode::getName() const
{
	return name;
}

const StructureNode::Branches & StructureNode::getBranches() const
{
	return branches;
}



int StructureNode::getBranchLocation(int token)
{
	if (branchLocations.count(token))
		return branchLocations[token];
	return -1;
}



StructureNode & StructureNode::fork()
{
	assert(branchStack.empty() && "trying to fork with unterminated branches");
	branches.push_back(Tokens());
	return *this;
}

StructureNode & StructureNode::add(StructureToken * token)
{
	assert(!branches.empty() && "no branch forked to add to");
	branches.back().push_back(token);
	return *this;
}

StructureNode & StructureNode::safe()
{
	assert(!branches.empty() && !branches.back().empty() && "no token to be marked safe");
	branches.back().back()->safe = true;
	return *this;
}

StructureNode & StructureNode::many()
{
	assert(!branches.empty() && "no branch forked to start many-group");
	branchStack.push(branches.back().size());
	branches.back().push_back(new StructureToken(StructureToken::Many));
	return *this;
}

StructureNode & StructureNode::opt()
{
	assert(!branches.empty() && "no branch forked to start optional-group");
	branchStack.push(branches.back().size());
	branches.back().push_back(new StructureToken(StructureToken::Optional));
	return *this;
}

StructureNode & StructureNode::done()
{
	assert(!branches.empty() && !branchStack.empty() && "no branch forked to end group");
	
	//Store the branch locations. Branching always works in the forward direction, i.e. to this
	//token, but not always into the other (e.g. with optional tokens).
	int x = branches.back().size();
	if (branches.back()[branchStack.top()]->type != StructureToken::Optional)
		branchLocations[x] = branchStack.top();
	branchLocations[branchStack.top()] = x;
	
	branches.back().push_back(new StructureToken(StructureToken::Done));
	branchStack.pop();
	return *this;
}



StructureNode::operator std::string ()
{
	std::stringstream out;
	out << name << std::endl;
	for (Branches::iterator b = branches.begin(); b != branches.end(); b++) {
		out << "|";
		for (Tokens::iterator t = (*b).begin(); t != (*b).end(); t++)
			out << " " << (std::string)**t;
		out << std::endl;
	}
	return out.str();
}
