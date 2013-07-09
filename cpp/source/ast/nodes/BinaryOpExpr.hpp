/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include "../Node.hpp"
#include "../Coder.hpp"
#include "interfaces.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <boost/smart_ptr.hpp>
#include <stdexcept>

namespace ast {

using std::vector;
using std::string;
using std::stringstream;
using std::endl;
using std::runtime_error;

class BinaryOpExpr : public Node
{
public:
	BinaryOpExpr() : Node(),
		interfaceGraph(this),
		interfaceCall(this),
		interfaceType(this) {}

	virtual bool isKindOf(Kind k)
	{
		if (Node::isKindOf(k)) return true;
		return k == kBinaryOpExpr;
	}

	virtual string getClassName() const { return "BinaryOpExpr"; }

	void setGraphPrev(const NodePtr& v)
	{
		if (!v && graphPrev) {
			modify();
			graphPrev.reset();
		}
		if (!graphPrev || v->getId() != graphPrev.id) {
			modify();
			graphPrev.set(v);
		}
	}
	void setGraphPrev(const NodeId& v)
	{
		if (v != graphPrev.id) {
			modify();
			graphPrev.set(v);
		}
	}
	const NodePtr& getGraphPrev()
	{
		return graphPrev.get(repository);
	}

	void setCallName(const string& v)
	{
		if (v != callName) {
			modify();
			callName = v;
		}
	}
	const string& getCallName()
	{
		return callName;
	}

	void setCallArgs(const NodeVector& v)
	{
		if (v != callArgs) {
			modify();
			callArgs = v;
		}
	}
	const NodeVector& getCallArgs()
	{
		return callArgs;
	}

	void setCallCandidates(const NodeVector& v)
	{
		if (v != callCandidates) {
			modify();
			callCandidates = v;
		}
	}
	const NodeVector& getCallCandidates()
	{
		return callCandidates;
	}

	void setSelectedCallCandidate(const NodePtr& v)
	{
		if (v && !v->isKindOf(kCallCandidate)) {
			throw runtime_error("'selectedCallCandidate' needs to be of kind {CallCandidate} or implement interface {}.");
		}
		if (!v && selectedCallCandidate) {
			modify();
			selectedCallCandidate.reset();
		}
		if (!selectedCallCandidate || v->getId() != selectedCallCandidate.id) {
			modify();
			selectedCallCandidate.set(v);
		}
	}
	void setSelectedCallCandidate(const NodeId& v)
	{
		if (v != selectedCallCandidate.id) {
			modify();
			selectedCallCandidate.set(v);
		}
	}
	const NodePtr& getSelectedCallCandidate()
	{
		return selectedCallCandidate.get(repository);
	}

	void setPossibleType(const NodePtr& v)
	{
		if (v != possibleType) {
			modify();
			possibleType = v;
		}
	}
	const NodePtr& getPossibleType()
	{
		return possibleType;
	}

	void setRequiredType(const NodePtr& v)
	{
		if (v != requiredType) {
			modify();
			requiredType = v;
		}
	}
	const NodePtr& getRequiredType()
	{
		return requiredType;
	}

	void setActualType(const NodePtr& v)
	{
		if (v != actualType) {
			modify();
			actualType = v;
		}
	}
	const NodePtr& getActualType()
	{
		return actualType;
	}

	void setOperatorName(const string& v)
	{
		if (v != operatorName) {
			modify();
			operatorName = v;
		}
	}
	const string& getOperatorName()
	{
		return operatorName;
	}

	void setLhs(const NodePtr& v)
	{
		if (v != lhs) {
			modify();
			lhs = v;
		}
	}
	const NodePtr& getLhs()
	{
		return lhs;
	}

	void setRhs(const NodePtr& v)
	{
		if (v != rhs) {
			modify();
			rhs = v;
		}
	}
	const NodePtr& getRhs()
	{
		return rhs;
	}

	virtual string describe(int depth = -1)
	{
		if (depth == 0) return "BinaryOpExpr{…}";
		stringstream str, b;
		str << "BinaryOpExpr{";
		if (this->graphPrev) b << endl << "  \033[1mgraphPrev\033[0m = " << "\033[36m" << this->graphPrev.id << "\033[0m";
		if (!this->callName.empty()) b << endl << "  \033[1mcallName\033[0m = '\033[33m" << this->callName << "\033[0m'";
		if (!this->callArgs.empty()) b << endl << "  \033[1mcallArgs\033[0m = " << indent(describeVector(this->callArgs, depth-1)) << "";
		if (!this->callCandidates.empty()) b << endl << "  \033[1mcallCandidates\033[0m = " << indent(describeVector(this->callCandidates, depth-1)) << "";
		if (this->selectedCallCandidate) b << endl << "  \033[1mselectedCallCandidate\033[0m = " << "\033[36m" << this->selectedCallCandidate.id << "\033[0m";
		if (this->possibleType) b << endl << "  \033[1mpossibleType\033[0m = " << indent(this->possibleType->describe(depth-1));
		if (this->requiredType) b << endl << "  \033[1mrequiredType\033[0m = " << indent(this->requiredType->describe(depth-1));
		if (this->actualType) b << endl << "  \033[1mactualType\033[0m = " << indent(this->actualType->describe(depth-1));
		if (!this->operatorName.empty()) b << endl << "  \033[1moperatorName\033[0m = '\033[33m" << this->operatorName << "\033[0m'";
		if (this->lhs) b << endl << "  \033[1mlhs\033[0m = " << indent(this->lhs->describe(depth-1));
		if (this->rhs) b << endl << "  \033[1mrhs\033[0m = " << indent(this->rhs->describe(depth-1));
		string bs = b.str();
		if (!bs.empty()) str << bs << endl;
		str << "}";
		return str.str();
	}

	virtual void encode(Encoder& e)
	{
		e.encode(this->graphPrev);
		e.encode(this->callName);
		e.encode(this->callArgs);
		e.encode(this->callCandidates);
		e.encode(this->selectedCallCandidate);
		e.encode(this->possibleType);
		e.encode(this->requiredType);
		e.encode(this->actualType);
		e.encode(this->operatorName);
		e.encode(this->lhs);
		e.encode(this->rhs);
	}

	virtual void decode(Decoder& d)
	{
		d.decode(this->graphPrev);
		d.decode(this->callName);
		d.decode(this->callArgs);
		d.decode(this->callCandidates);
		d.decode(this->selectedCallCandidate);
		d.decode(this->possibleType);
		d.decode(this->requiredType);
		d.decode(this->actualType);
		d.decode(this->operatorName);
		d.decode(this->lhs);
		d.decode(this->rhs);
	}

	virtual void updateHierarchy(const NodeId& id, Repository* repository = NULL, Node* parent = NULL)
	{
		Node::updateHierarchy(id, repository, parent);
		for (int i = 0; i < this->callArgs.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->callArgs[i]->updateHierarchy((id + "callArgs") + buf, repository, this);
		}
		for (int i = 0; i < this->callCandidates.size(); i++) {
			char buf[32]; snprintf(buf, 31, "%i", i);
			this->callCandidates[i]->updateHierarchy((id + "callCandidates") + buf, repository, this);
		}
		if (this->possibleType) this->possibleType->updateHierarchy(id + "possibleType", repository, this);
		if (this->requiredType) this->requiredType->updateHierarchy(id + "requiredType", repository, this);
		if (this->actualType) this->actualType->updateHierarchy(id + "actualType", repository, this);
		if (this->lhs) this->lhs->updateHierarchy(id + "lhs", repository, this);
		if (this->rhs) this->rhs->updateHierarchy(id + "rhs", repository, this);
	}

	virtual const NodePtr& resolvePath(const string& path)
	{
		size_t size = path.size();
		// .*
		if (true) {
			// actualType.*
			if (size >= 10 && path[0] == 'a' && path[1] == 'c' && path[2] == 't' && path[3] == 'u' && path[4] == 'a' && path[5] == 'l' && path[6] == 'T' && path[7] == 'y' && path[8] == 'p' && path[9] == 'e') {
				// actualType
				if (size == 10) {
					return getActualType();
				} else if (path[10] == '.') {
					return getActualType()->resolvePath(path.substr(11));
				}
			}
			// call.*
			if (size >= 4 && path[0] == 'c' && path[1] == 'a' && path[2] == 'l' && path[3] == 'l') {
				// callArgs.*
				if (size >= 8 && path[4] == 'A' && path[5] == 'r' && path[6] == 'g' && path[7] == 's') {
					// callArgs
					if (size == 8) {
						throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
					} else if (path[8] == '.') {
						size_t dot = path.find(".", 9);
						string idx_str = path.substr(9, dot);
						int idx = atoi(idx_str.c_str());
						const NodeVector& a = getCallArgs();
						if (idx < 0 || idx >= a.size()) {
							throw std::runtime_error("Index into array '" + path.substr(0, 8) + "' is out of bounds.");
						}
						if (dot == string::npos) {
							return a[idx];
						} else {
							return a[idx]->resolvePath(path.substr(dot + 1));
						}
					}
				}
				// callCandidates.*
				if (size >= 14 && path[4] == 'C' && path[5] == 'a' && path[6] == 'n' && path[7] == 'd' && path[8] == 'i' && path[9] == 'd' && path[10] == 'a' && path[11] == 't' && path[12] == 'e' && path[13] == 's') {
					// callCandidates
					if (size == 14) {
						throw std::runtime_error("Path '" + path + "' refers to an array instead of a concrete array element.");
					} else if (path[14] == '.') {
						size_t dot = path.find(".", 15);
						string idx_str = path.substr(15, dot);
						int idx = atoi(idx_str.c_str());
						const NodeVector& a = getCallCandidates();
						if (idx < 0 || idx >= a.size()) {
							throw std::runtime_error("Index into array '" + path.substr(0, 14) + "' is out of bounds.");
						}
						if (dot == string::npos) {
							return a[idx];
						} else {
							return a[idx]->resolvePath(path.substr(dot + 1));
						}
					}
				}
			}
			// graphPrev.*
			if (size >= 9 && path[0] == 'g' && path[1] == 'r' && path[2] == 'a' && path[3] == 'p' && path[4] == 'h' && path[5] == 'P' && path[6] == 'r' && path[7] == 'e' && path[8] == 'v') {
				// graphPrev
				if (size == 9) {
					return getGraphPrev();
				} else if (path[9] == '.') {
					return getGraphPrev()->resolvePath(path.substr(10));
				}
			}
			// lhs.*
			if (size >= 3 && path[0] == 'l' && path[1] == 'h' && path[2] == 's') {
				// lhs
				if (size == 3) {
					return getLhs();
				} else if (path[3] == '.') {
					return getLhs()->resolvePath(path.substr(4));
				}
			}
			// possibleType.*
			if (size >= 12 && path[0] == 'p' && path[1] == 'o' && path[2] == 's' && path[3] == 's' && path[4] == 'i' && path[5] == 'b' && path[6] == 'l' && path[7] == 'e' && path[8] == 'T' && path[9] == 'y' && path[10] == 'p' && path[11] == 'e') {
				// possibleType
				if (size == 12) {
					return getPossibleType();
				} else if (path[12] == '.') {
					return getPossibleType()->resolvePath(path.substr(13));
				}
			}
			// r.*
			if (size >= 1 && path[0] == 'r') {
				// requiredType.*
				if (size >= 12 && path[1] == 'e' && path[2] == 'q' && path[3] == 'u' && path[4] == 'i' && path[5] == 'r' && path[6] == 'e' && path[7] == 'd' && path[8] == 'T' && path[9] == 'y' && path[10] == 'p' && path[11] == 'e') {
					// requiredType
					if (size == 12) {
						return getRequiredType();
					} else if (path[12] == '.') {
						return getRequiredType()->resolvePath(path.substr(13));
					}
				}
				// rhs.*
				if (size >= 3 && path[1] == 'h' && path[2] == 's') {
					// rhs
					if (size == 3) {
						return getRhs();
					} else if (path[3] == '.') {
						return getRhs()->resolvePath(path.substr(4));
					}
				}
			}
			// selectedCallCandidate.*
			if (size >= 21 && path[0] == 's' && path[1] == 'e' && path[2] == 'l' && path[3] == 'e' && path[4] == 'c' && path[5] == 't' && path[6] == 'e' && path[7] == 'd' && path[8] == 'C' && path[9] == 'a' && path[10] == 'l' && path[11] == 'l' && path[12] == 'C' && path[13] == 'a' && path[14] == 'n' && path[15] == 'd' && path[16] == 'i' && path[17] == 'd' && path[18] == 'a' && path[19] == 't' && path[20] == 'e') {
				// selectedCallCandidate
				if (size == 21) {
					return getSelectedCallCandidate();
				} else if (path[21] == '.') {
					return getSelectedCallCandidate()->resolvePath(path.substr(22));
				}
			}
		}
		throw std::runtime_error("Node path '" + path + "' does not point to a node or array of nodes.");
	}

	virtual NodeVector getChildren()
	{
		NodeVector v;
		if (const NodePtr& n = this->getLhs()) v.push_back(n);
		if (const NodePtr& n = this->getRhs()) v.push_back(n);
		return v;
	}

	// Interfaces
	virtual GraphInterface* asGraph() { return &this->interfaceGraph; }
	virtual CallInterface* asCall() { return &this->interfaceCall; }
	virtual TypeInterface* asType() { return &this->interfaceType; }

protected:
	NodeRef graphPrev;
	string callName;
	NodeVector callArgs;
	NodeVector callCandidates;
	NodeRef selectedCallCandidate;
	NodePtr possibleType;
	NodePtr requiredType;
	NodePtr actualType;
	string operatorName;
	NodePtr lhs;
	NodePtr rhs;

	// Interfaces
	GraphInterfaceImpl<BinaryOpExpr> interfaceGraph;
	CallInterfaceImpl<BinaryOpExpr> interfaceCall;
	TypeInterfaceImpl<BinaryOpExpr> interfaceType;
};

} // namespace ast