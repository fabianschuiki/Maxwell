/* Copyright © 2013-2014 Fabian Schuiki */
#pragma once
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
	};

	enum {
		kTypeStage = 0,
		kFuncStage,
		kMainStage
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
		typedef vector<string> Stmts;

		BlockContext *parent;
		SymbolSet usedSymbols;
		VarMap vars;
		Stmts stmts;
		int tmpIndex;
		string resVar;

		BlockContext() {
			parent = NULL;
			tmpIndex = 0;
		}

		BlockContext(BlockContext* p) {
			vars = p->vars;
			usedSymbols = p->usedSymbols;
			resVar = p->resVar;
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
		kAssignmentPrec,
		kLowestPrec
	};

private:
	string dumpContext(const BlockContext& ctx);
};

} // namespace backendc