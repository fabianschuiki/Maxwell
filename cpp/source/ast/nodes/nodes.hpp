/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include <string>

#include "BinaryOpExpr.hpp"
#include "CallArg.hpp"
#include "CallCandidate.hpp"
#include "CallExpr.hpp"
#include "ExprStmt.hpp"
#include "FuncArg.hpp"
#include "FuncArgTuple.hpp"
#include "FuncBody.hpp"
#include "FuncDef.hpp"
#include "GenericType.hpp"
#include "IdentifierExpr.hpp"
#include "NamedType.hpp"
#include "TypeDef.hpp"
#include "UnionType.hpp"
#include "VarDefExpr.hpp"

namespace ast {

using std::string;

/// Node factory.
class NodeFactory
{
public:
	static NodePtr make(const string& name)
	{
		size_t size = name.size();
		// .*
		if (true) {
			// BinaryOpExpr.*
			if (size >= 12 && name[0] == 'B' && name[1] == 'i' && name[2] == 'n' && name[3] == 'a' && name[4] == 'r' && name[5] == 'y' && name[6] == 'O' && name[7] == 'p' && name[8] == 'E' && name[9] == 'x' && name[10] == 'p' && name[11] == 'r') {
				// BinaryOpExpr
				if (size == 12) return NodePtr(new BinaryOpExpr);
			}
			// Call.*
			if (size >= 4 && name[0] == 'C' && name[1] == 'a' && name[2] == 'l' && name[3] == 'l') {
				// CallArg.*
				if (size >= 7 && name[4] == 'A' && name[5] == 'r' && name[6] == 'g') {
					// CallArg
					if (size == 7) return NodePtr(new CallArg);
				}
				// CallCandidate.*
				if (size >= 13 && name[4] == 'C' && name[5] == 'a' && name[6] == 'n' && name[7] == 'd' && name[8] == 'i' && name[9] == 'd' && name[10] == 'a' && name[11] == 't' && name[12] == 'e') {
					// CallCandidate
					if (size == 13) return NodePtr(new CallCandidate);
				}
				// CallExpr.*
				if (size >= 8 && name[4] == 'E' && name[5] == 'x' && name[6] == 'p' && name[7] == 'r') {
					// CallExpr
					if (size == 8) return NodePtr(new CallExpr);
				}
			}
			// ExprStmt.*
			if (size >= 8 && name[0] == 'E' && name[1] == 'x' && name[2] == 'p' && name[3] == 'r' && name[4] == 'S' && name[5] == 't' && name[6] == 'm' && name[7] == 't') {
				// ExprStmt
				if (size == 8) return NodePtr(new ExprStmt);
			}
			// Func.*
			if (size >= 4 && name[0] == 'F' && name[1] == 'u' && name[2] == 'n' && name[3] == 'c') {
				// FuncArg.*
				if (size >= 7 && name[4] == 'A' && name[5] == 'r' && name[6] == 'g') {
					// FuncArg
					if (size == 7) return NodePtr(new FuncArg);
					// FuncArgTuple.*
					if (size >= 12 && name[7] == 'T' && name[8] == 'u' && name[9] == 'p' && name[10] == 'l' && name[11] == 'e') {
						// FuncArgTuple
						if (size == 12) return NodePtr(new FuncArgTuple);
					}
				}
				// FuncBody.*
				if (size >= 8 && name[4] == 'B' && name[5] == 'o' && name[6] == 'd' && name[7] == 'y') {
					// FuncBody
					if (size == 8) return NodePtr(new FuncBody);
				}
				// FuncDef.*
				if (size >= 7 && name[4] == 'D' && name[5] == 'e' && name[6] == 'f') {
					// FuncDef
					if (size == 7) return NodePtr(new FuncDef);
				}
			}
			// GenericType.*
			if (size >= 11 && name[0] == 'G' && name[1] == 'e' && name[2] == 'n' && name[3] == 'e' && name[4] == 'r' && name[5] == 'i' && name[6] == 'c' && name[7] == 'T' && name[8] == 'y' && name[9] == 'p' && name[10] == 'e') {
				// GenericType
				if (size == 11) return NodePtr(new GenericType);
			}
			// IdentifierExpr.*
			if (size >= 14 && name[0] == 'I' && name[1] == 'd' && name[2] == 'e' && name[3] == 'n' && name[4] == 't' && name[5] == 'i' && name[6] == 'f' && name[7] == 'i' && name[8] == 'e' && name[9] == 'r' && name[10] == 'E' && name[11] == 'x' && name[12] == 'p' && name[13] == 'r') {
				// IdentifierExpr
				if (size == 14) return NodePtr(new IdentifierExpr);
			}
			// NamedType.*
			if (size >= 9 && name[0] == 'N' && name[1] == 'a' && name[2] == 'm' && name[3] == 'e' && name[4] == 'd' && name[5] == 'T' && name[6] == 'y' && name[7] == 'p' && name[8] == 'e') {
				// NamedType
				if (size == 9) return NodePtr(new NamedType);
			}
			// TypeDef.*
			if (size >= 7 && name[0] == 'T' && name[1] == 'y' && name[2] == 'p' && name[3] == 'e' && name[4] == 'D' && name[5] == 'e' && name[6] == 'f') {
				// TypeDef
				if (size == 7) return NodePtr(new TypeDef);
			}
			// UnionType.*
			if (size >= 9 && name[0] == 'U' && name[1] == 'n' && name[2] == 'i' && name[3] == 'o' && name[4] == 'n' && name[5] == 'T' && name[6] == 'y' && name[7] == 'p' && name[8] == 'e') {
				// UnionType
				if (size == 9) return NodePtr(new UnionType);
			}
			// VarDefExpr.*
			if (size >= 10 && name[0] == 'V' && name[1] == 'a' && name[2] == 'r' && name[3] == 'D' && name[4] == 'e' && name[5] == 'f' && name[6] == 'E' && name[7] == 'x' && name[8] == 'p' && name[9] == 'r') {
				// VarDefExpr
				if (size == 10) return NodePtr(new VarDefExpr);
			}
		}
		throw std::runtime_error("Node class name '" + name + "' not known to NodeFactory.");
	}
};

} // namespace ast

