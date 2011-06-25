#pragma once
#include "node.h"


class StructureRoot : public StructureNode {
private:
	std::vector<StructureNode *> nodes;
	
public:
	StructureRoot();
	~StructureRoot();
};
