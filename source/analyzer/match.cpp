#include <assert.h>
#include <iostream>
#include <set>
#include "match.h"
#include "stringdiff.h"

std::map<const Match * const, float> Match::unsafeMatchCache;
std::map<const Match * const, float> Match::seriesMatchCache;



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
	
	expiresIn = -1;
	
	unsafeMatchCache.erase(this);
	seriesMatchCache.erase(this);
}

Match::~Match()
{
	if (next)
		delete next;
	parent = next = prev = nextSibling = prevSibling = NULL;
	unsafeMatchCache.erase(this);
	seriesMatchCache.erase(this);
}



StructureToken * Match::getStructureToken() const
{
	return structureToken;
}

StructureNode * Match::getStructureNode() const
{
	return node;
}



void Match::findNextToken(int cn, StructureNode ** nn, int * nb, int * nt, Match ** nm) const
{
	if (cn < 0)
		cn = tokenIndex;
	
	//If theres another token left in the node, that's our next token.
	if (node && (cn + 1) < node->getBranches()[branchIndex].size()) {
		*nn = node;
		*nb = branchIndex;
		*nt = cn + 1;
		*nm = this->parent;
	}
	
	//Otherwise we have to ask our parent what the next token is since we've reached the end of our
	//branch.
	else if (parent) {
		parent->findNextToken(-1, nn, nb, nt, nm);
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
		m->parent = this;
		m->expiresIn = expiresIn;
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
	//Fill a vector of ints with token locations that we need to find the next token of and create
	//successive matches.
	std::vector<int> tokenOffsets;
	tokenOffsets.push_back(tokenIndex);
	
	//If this is an optional token we have to created two branches, one proceeding from the current
	//location and one skipping ahead to the token after the done statement.
	if (nt->isBranch()) {
		int branch = node->getBranchLocation(tokenIndex);
		if (branch >= 0)
			tokenOffsets.push_back(branch);
	}
	
	//Iterate through the token offsets and create a new match for each.
	Match * last = NULL;
	for (int i = 0; i < tokenOffsets.size(); i++) {
		
		//Find the next token.
		StructureNode * nextNode;
		int nextBranch, nextToken;
		Match * nextParent;
		findNextToken(tokenOffsets[i], &nextNode, &nextBranch, &nextToken, &nextParent);
		
		//If we haven't found a new token just skip ahead.
		if (!nextNode)
			continue;
		
		//Create a new match for the given node, branch and token index.
		Match * m = new Match(nextNode, nextBranch, nextToken);
		m->prev = this;
		m->parent = nextParent;
		m->expiresIn = expiresIn;
		
		//Link the match into the tree.
		if (!next) next = m;
		m->prevSibling = last;
		if (last) last->nextSibling = m;
		last = m;
		
		//Based on whether we perform any token matching, we pass on our token to the match or get
		//the successive token and pass that.
		if (nt->dontMatch())
			m->setToken(token);
		else
			m->setToken(token ? token->next : NULL);
	}
}



float Match::getMatch() const
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

Token * Match::getToken() const
{
	return token;
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



bool Match::isSafe() const
{
	return safe;
}

void Match::setSafe(bool s)
{
	safe = s;
}

bool Match::isSafeMatch() const
{
	return (safe && getUnsafeMatch() >= /*(1 - 1e-5)*/0.95);
}

bool Match::dontMatch() const
{
	if (!structureToken) return true;
	return structureToken->dontMatch();
}



float Match::getUnsafeMatch() const
{
	float v;
	if (!unsafeMatchCache.count(this)) {
		
		const Match * m = this;
		float summedMatches = 0;
		int matchCount = 0;
		while (m && (m == this || !m->isSafe())) {
			if (!m->dontMatch()) {
				summedMatches += m->match;
				matchCount++;
			}
			m = m->prev;
		}
		v = (summedMatches / matchCount);
		
		unsafeMatchCache[this] = v;
	} else {
		v = unsafeMatchCache[this];
	}
	return v;
}

float Match::getSeriesMatch() const
{
	float v;
	if (!seriesMatchCache.count(this)) {
		
		const Match * m = this;
		float summedMatches = 0;
		int matchCount = 0;
		while (m) {
			if (!m->dontMatch()) {
				summedMatches += m->match;
				matchCount++;
			}
			m = m->prev;
		}
		v = (summedMatches / matchCount);
		
		seriesMatchCache[this] = v;
	} else {
		v = seriesMatchCache[this];
	}
	return v;
}



bool Match::isRecursive() const
{
	return (structureToken && prev && prev->structureToken &&
			structureToken->type == StructureToken::Reference &&
			prev->structureToken->type == StructureToken::Reference &&
			structureToken->reference == prev->structureToken->reference);
}



void Match::compare()
{
	match = 0;
	
	//There are no compares for reference tokens.
	if (!structureToken || structureToken->dontMatch())
		return;
	
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
			if (token->kind == Token::kSymbolToken) {
				if (token->text == structureToken->text)
					match = 1;
				else {
					static std::vector<std::set<std::string> > closelyRelated;
					static std::vector<std::set<std::string> > looselyRelated;
					if (closelyRelated.empty()) {
						closelyRelated.resize(closelyRelated.size() + 1);
						closelyRelated.back().insert(":");
						closelyRelated.back().insert(".");
						closelyRelated.resize(closelyRelated.size() + 1);
						closelyRelated.back().insert(";");
						closelyRelated.back().insert(",");
					}
					if (looselyRelated.empty()) {
						looselyRelated.resize(looselyRelated.size() + 1);
						looselyRelated.back().insert(",");
						looselyRelated.back().insert(".");
						looselyRelated.resize(looselyRelated.size() + 1);
						looselyRelated.back().insert(";");
						looselyRelated.back().insert(":");
					}
					
					if (match < 0.66) {
						for (int i = 0; i < closelyRelated.size(); i++) {
							if (closelyRelated[i].count(token->text) &&
								closelyRelated[i].count(structureToken->text)) {
								match = 0.66;
								break;
							}
						}
					}
					if (match < 0.33) {
						for (int i = 0; i < looselyRelated.size(); i++) {
							if (looselyRelated[i].count(token->text) &&
								looselyRelated[i].count(structureToken->text)) {
								match = 0.33;
								break;
							}
						}
					}
				}
			}
		} break;
	}
}



Match::operator std::string () const
{
	if (!structureToken || (!prev && !parent))
		return "";
	std::stringstream out;
	if (/*!safe &&*/ prev)
		out << (std::string)*prev;
	if (!structureToken->dontMatch()) {
		if (!out.str().empty())
			out << " ";
		out << (std::string)*structureToken;
		/*if (safe)
			out << "[" << getUnsafeMatch() * 100 << "%]";
		if (structureToken->type == StructureToken::Symbol)
			out << "[" << match * 100 << "%]";*/
	}
	return out.str();
}
