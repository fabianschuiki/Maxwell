/* Automatically generated by ast-gen. DO NOT MODIFY. */
#pragma once
#include <string>

#include "ExprStmt.hpp"
#include "FuncArg.hpp"
#include "FuncArgTuple.hpp"
#include "FuncBody.hpp"
#include "FunctionDefinition.hpp"
#include "IdentifierExpr.hpp"

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
				// FunctionDefinition.*
				if (size >= 18 && name[4] == 't' && name[5] == 'i' && name[6] == 'o' && name[7] == 'n' && name[8] == 'D' && name[9] == 'e' && name[10] == 'f' && name[11] == 'i' && name[12] == 'n' && name[13] == 'i' && name[14] == 't' && name[15] == 'i' && name[16] == 'o' && name[17] == 'n') {
					// FunctionDefinition
					if (size == 18) return NodePtr(new FunctionDefinition);
				}
			}
			// IdentifierExpr.*
			if (size >= 14 && name[0] == 'I' && name[1] == 'd' && name[2] == 'e' && name[3] == 'n' && name[4] == 't' && name[5] == 'i' && name[6] == 'f' && name[7] == 'i' && name[8] == 'e' && name[9] == 'r' && name[10] == 'E' && name[11] == 'x' && name[12] == 'p' && name[13] == 'r') {
				// IdentifierExpr
				if (size == 14) return NodePtr(new IdentifierExpr);
			}
		}
		throw std::runtime_error("Node class name '" + name + "' not known to NodeFactory.");
	}
};

} // namespace ast

