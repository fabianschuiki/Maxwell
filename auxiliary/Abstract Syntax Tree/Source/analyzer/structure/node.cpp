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



StructureNode & StructureNode::fork()
{
	branches.push_back(Tokens());
	return *this;
}

StructureNode & StructureNode::add(StructureToken * token)
{
	assert(!branches.empty() && "no branch forked to add to");
	branches.back().push_back(token);
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
