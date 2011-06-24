#pragma once
#include "../../tokenizer/token.h"
#include "../structure/node.h"


class Match {
private:
	StructureNode * const node;
	const int branchIndex;
	const int tokenIndex;
	StructureToken * const structureToken;
	
	float match;
	
protected:
	Token * token;
	
	Match * parent;
	Match * next;
	Match * prev;
	Match * nextSibling;
	Match * prevSibling;
	
	bool safe;
	
public:
	Match(StructureNode * node, int branchIndex, int tokenIndex);
	~Match();
	
	StructureToken * getStructureToken();
	
	void findNextToken(StructureNode ** nextNode, int * nextBranch, int * nextToken) const;
	void makeNextMatch();
	void makeNextMatch(StructureNode * nextNode);
	void makeNextMatch(StructureToken * nextToken);
	
	float getMatch();
	void setToken(Token * token);
	
	Match * getParent() const;
	Match * getNext() const;
	Match * getPrev() const;
	Match * getNextSibling() const;
	Match * getPrevSibling() const;
	
	bool getSafe() const;
	void setSafe(bool safe);
	
	float getUnsafeMatch();
	
	void compare();
};
