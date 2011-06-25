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
	
	static std::map<const Match * const, float> unsafeMatchCache;
	
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
	
	StructureNode * getStructureNode() const;
	StructureToken * getStructureToken() const;
	
	void findNextToken(int currentToken, StructureNode ** nextNode, int * nextBranch,
					   int * nextToken, Match ** nextParent) const;
	void makeNextMatch();
	void makeNextMatch(StructureNode * nextNode);
	void makeNextMatch(StructureToken * nextToken);
	
	float getMatch() const;
	void setToken(Token * token);
	Token * getToken() const;
	
	Match * getParent() const;
	Match * getNext() const;
	Match * getPrev() const;
	Match * getNextSibling() const;
	Match * getPrevSibling() const;
	
	bool isSafe() const;
	void setSafe(bool safe);
	bool isSafeMatch() const;
	bool dontMatch() const;
	
	float getUnsafeMatch() const;
	
	void compare();
	
	operator std::string () const;
};
