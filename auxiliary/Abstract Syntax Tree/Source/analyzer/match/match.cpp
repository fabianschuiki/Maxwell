#include <assert.h>
#include <iostream>
#include "match.h"
#include "../../stringdiff.h"


Match::Match(StructureNode * n, int b, int t) : node(n), branchIndex(b), tokenIndex(t),
structureToken(n ? n->getBranches()[b][t] : NULL)
{
	match = 0;
	
	parent = NULL;
	next = NULL;
	prev = NULL;
	nextSibling = NULL;
	prevSibling = NULL;
	
	safe = (structureToken && structureToken->safe);
}

Match::~Match()
{
	if (next)
		delete next;
	parent = next = prev = nextSibling = prevSibling = NULL;
}



StructureToken * Match::getStructureToken()
{
	return structureToken;
}



void Match::findNextToken(StructureNode ** nn, int * nb, int * nt) const
{
	//If theres another token left in the node, that's our next token.
	if (node && (tokenIndex + 1) < node->getBranches()[branchIndex].size()) {
		*nn = node;
		*nb = branchIndex;
		*nt = tokenIndex + 1;
	}
	
	//Otherwise we have to ask our parent what the next token is since we've reached the end of our
	//branch.
	else if (parent) {
		parent->findNextToken(nn, nb, nt);
	}
	
	//Otherwise there's simply nothing left in the structure.
	else {
		*nn = NULL;
	}
}

void Match::makeNextMatch()
{
	if (!node) return;
	assert(next == NULL && "there's already a next match");
	
	//First we have to check if our token is a reference or not. If it is a reference we have to
	//create multiple successive matches.
	StructureToken * t = structureToken;
	if (t->type == StructureToken::Reference)
		makeNextMatch(t->reference);
	else
		makeNextMatch(t);
}

void Match::makeNextMatch(StructureNode * nextNode)
{
	Match * last = NULL;
	
	//Iterate through the node's branches and create a new match for each.
	int branchCount = nextNode->getBranches().size();
	for (int b = 0; b < branchCount; b++) {
		Match * m = new Match(nextNode, b, 0);
		m->prev = this;
		m->setToken(token);
		
		//If this is the first successor, make it our next.
		if (!next)
			next = m;
		
		//If there's already a match there, set its next pointer to the new match, and vice versa.
		if (last) {
			last->nextSibling = m;
			m->prevSibling = last;
		}
		last = m;
	}
}

void Match::makeNextMatch(StructureToken * nt)
{
	//Find our next token.
	StructureNode * nextNode;
	int nextBranch, nextToken;
	findNextToken(&nextNode, &nextBranch, &nextToken);
	
	//If we haven't found a new token there's nothing left to do.
	if (!nextNode)
		return;
	
	//Create a new match for the given node, branch and token index.
	next = new Match(nextNode, nextBranch, nextToken);
	next->prev = this;
	next->setToken(token ? token->next : NULL);
}



float Match::getMatch()
{
	return match;
}

void Match::setToken(Token * t)
{
	if (token != t) {
		token = t;
		if (token)
			compare();
	}
}



Match * Match::getParent() const
{
	return parent;
}

Match * Match::getNext() const
{
	return next;
}

Match * Match::getPrev() const
{
	return prev;
}

Match * Match::getNextSibling() const
{
	return nextSibling;
}

Match * Match::getPrevSibling() const
{
	return prevSibling;
}



bool Match::getSafe() const
{
	return safe;
}

void Match::setSafe(bool s)
{
	safe = s;
}



float Match::getUnsafeMatch()
{
	Match * m = this;
	float usm = 0;
	int usmc = 0;
	while (m && (!m->safe || m == this)) {
		if (m->structureToken->type != StructureToken::Reference) {
			usm += m->getMatch();
			usmc++;
		}
		m = m->prev;
	}
	return usm / usmc;
}



void Match::compare()
{
	match = 0;
	
	//There are no compares for reference tokens.
	if (!structureToken || structureToken->type == StructureToken::Reference) {
		//match = 1;
		return;
	}
	
	//Based on the structure token we have to choose a different compare function.
	switch (structureToken->type) {
		case StructureToken::Identifier:
			match = (token->kind == Token::kIdentifierToken	? 1.0 : 0.0); break;
		case StructureToken::Numeric:
			match = (token->kind == Token::kNumericToken	? 1.0 : 0.0); break;
		case StructureToken::String:
			match = (token->kind == Token::kStringToken		? 1.0 : 0.0); break;
			
		case StructureToken::Keyword: {
			if (token->kind == Token::kIdentifierToken) {
				StringDiff diff(structureToken->text, token->text);
				match = diff.getMatch();
			}
		} break;
			
		case StructureToken::Symbol: {
			//TODO: Distinguish between closely related symbol mismatches "((" instead of "()" and
			//other mistakes like "*&".
			match = (token->kind == Token::kSymbolToken &&
					 token->text == structureToken->text ? 1.0 : 0.0);
		} break;
	}
	
	//Dump some information.
	/*if (structureToken && structureToken->type != StructureToken::Reference)
		std::cout << "matching " << (std::string)*token << " against " << (std::string)*structureToken << " = " << match * 100 << "%" << std::endl;*/
}
