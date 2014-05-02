/* Copyright © 2013-2014 Fabian Schuiki */
#pragma once
#include "TypeSnippet.hpp"
#include <ast/Node.hpp>
#include <ast/Repository.hpp>
#include <ast/nodes/ast.hpp>
#include <string>
#include <set>
#include <map>

namespace backendc {

using namespace ast;
using std::set;
using std::string;
using std::map;

class Repository;

/**
 * @brief Converts an AST into C code.
 *
 * This class operates on nodes previously processed by the various stages
 * of the frontend. It generates compilable C code from these AST nodes and
 * throws exceptions whenever something could not be compiled.
 */
class CodeGenerator
{
public:
	ast::Repository& nodeRepository;
	backendc::Repository& backendRepository;

	CodeGenerator(ast::Repository& nr, backendc::Repository& br);

	struct RootContext {
		struct Stmt {
			int stage;
			string code;
			Stmt(int stage, const string& code): stage(stage), code(code) {}
			bool operator< (const Stmt& b) const {
				if (stage < b.stage) return true;
				if (stage > b.stage) return false;
				if (code < b.code) return true;
				if (code > b.code) return false;
				return false;
			}
		};
		typedef set<Stmt> Stmts;
		Stmts decls;
		Stmts defs;

		TypeSnippetTable types;
		int tupleIndex;
		int funcIndex;

		RootContext(): tupleIndex(1), funcIndex(1) {}
	};

	enum {
		kTypeStage = 0,
		kFuncStage
	};

	void run(const NodePtr& node, RootContext& context);
	void run(const NodeId& id, RootContext& context);

protected:
	string indent(const string& in);

	void generateFuncDef(const FuncDef::Ptr& node, RootContext& context);
	void generateTypeDef(const TypeDef::Ptr& node, RootContext& context);

	struct BlockContext {
		typedef set<string> SymbolSet;
		typedef map<NodeId, string> VarMap;
		typedef map<string, string> Typedefs;
		typedef vector<string> Stmts;

		RootContext *root;
		BlockContext *parent;
		SymbolSet usedSymbols;
		VarMap vars;
		Stmts stmts;
		Typedefs typedefs;
		int tmpIndex;
		string resVar;

		BlockContext() {
			root = NULL;
			parent = NULL;
			tmpIndex = 0;
		}

		explicit BlockContext(RootContext* r) {
			root = r;
			parent = NULL;
			tmpIndex = 0;
		}

		explicit BlockContext(BlockContext* p) {
			vars = p->vars;
			usedSymbols = p->usedSymbols;
			typedefs = p->typedefs;
			resVar = p->resVar;
			root = p->root;
			parent = p;
			tmpIndex = p->tmpIndex;
		}
	};

	struct ExprCode {
		string code;
		bool isRef;
		int precedence;

		ExprCode() {
			isRef = false;
			precedence = 0;
		}
	};

	ExprCode generateBlock(const BlockExpr::Ptr& node, BlockContext& context);
	ExprCode generateExpr(const NodePtr& node, BlockContext& context);
	string generateType(const NodePtr& node, BlockContext& context);

	string makeTmpVar(BlockContext& context);

	string precedenceWrapped(const string& s, int prec, int outer_prec);
	string precedenceWrapped(const ExprCode& ec, int outer_prec);

	// Enumeration that simplifies precedence handling.
	enum {
		kPrimaryPrec = 0,
		kPrefixPrec,
		kMultiplicativePrec,
		kAdditivePrec,
		kRelationalPrec,
		kEqualityPrec,
		kAndPrec,
		kOrPrec,
		kAssignmentPrec,
		kLowestPrec
	};

private:
	string dumpContext(const BlockContext& ctx);
};

} // namespace backendc