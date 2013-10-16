/* Copyright © 2013 Fabian Schuiki */
#include "CodeGenerator.hpp"
#include <ast/nodes/ast.hpp>
#include <iostream>
#include <sstream>

using namespace ast;
using backendc::CodeGenerator;
using std::cout;
using std::stringstream;
using std::string;


string CodeGenerator::dumpContext(const BlockContext& ctx)
{
	stringstream s;

	s << "\033[1mstmts\033[0m:\n";
	for (int i = 0; i < ctx.stmts.size(); i++) {
		s << "- " << indent(ctx.stmts[i]) << "\n";
	}

	s << "\033[1mvars (" << ctx.vars.size() << ")\033[0m:\n";
	for (map<NodeId, string>::const_iterator it = ctx.vars.begin(); it != ctx.vars.end(); it++) {
		s << "- " << it->first << " \"" << it->second << "\"\n"; 
	}

	s << "\033[1msymbols (" << ctx.usedSymbols.size() << ")\033[0m:\n";
	for (set<string>::const_iterator it = ctx.usedSymbols.begin(); it != ctx.usedSymbols.end(); it++) {
		s << "- " << *it << "\n";
	}

	return s.str();
}


CodeGenerator::CodeGenerator(ast::Repository& nr, backendc::Repository& br)
	: nodeRepository(nr), backendRepository(br)
{
}

/**
 * @brief Generates code for this node.
 */
void CodeGenerator::run(const NodePtr& node)
{
	if (const FuncDef::Ptr& func = FuncDef::from(node)) {
		generateFuncDef(func);
	} else if (const TypeDef::Ptr& type = TypeDef::from(node)) {
		generateTypeDef(type);
	} else {
		stringstream s;
		s << "Node " << node->getId() << " (" << node->getClassName() << ") cannot be compiled as a root node.";
		throw std::runtime_error(s.str());
	}
}

/**
 * @brief Generates code for the given node id.
 *
 * Looks up the node with the given id in the AST repository and calls run()
 * with that node as an argument.
 */
void CodeGenerator::run(const NodeId& id)
{
	run(nodeRepository.getNode(id));
}


void CodeGenerator::generateFuncDef(const FuncDef::Ptr& node)
{
	// Generate the code for the body.
	BlockContext bodyContext = BlockContext();
	ExprCode ec;
	const NodePtr& body = node->getBody();

	if (const BlockExpr::Ptr& block = BlockExpr::from(body)) {
		ec = generateBlock(block, bodyContext);
	} else {
		ec = generateExpr(body, bodyContext);
	}

	stringstream bodyCode;
	bodyCode << "{\n";
	for (vector<string>::iterator it = bodyContext.stmts.begin(); it != bodyContext.stmts.end(); it++) {
		bodyCode << "    " << indent(*it) << "\n";
	}
	if (node->getImplOut()) {
		bodyCode << "    return " << ec.code << ";\n";
	}
	bodyCode << "}";

	cout << "Body of func \033[33;1m" << node->getName() << "\033[0m:\n" << dumpContext(bodyContext) << "\n";
	cout << "Bare code: " << bodyCode.str() << "\n";
}

void CodeGenerator::generateTypeDef(const TypeDef::Ptr& node)
{

}

CodeGenerator::ExprCode CodeGenerator::generateBlock(const BlockExpr::Ptr& node, BlockContext& context)
{
	ExprCode code;
	string retVar;
	bool useRetVar = false;
	if (context.parent) {
		retVar = context.resVar;
		if (retVar.empty()) {
			retVar = makeTmpVar(context);
			context.stmts.push_back("void* " + retVar + ";");
		}
		code.code = retVar;
		code.isRef = true;
		useRetVar = true;
	} else {
		code.isRef = false;
		useRetVar = false;
	}

	const NodeVector& exprs = node->getExprs();
	for (NodeVector::const_iterator it = exprs.begin(); it != exprs.end();) {
		const NodePtr& expr = *it;
		it++;
		bool last = (it == exprs.end());

		ExprCode ec = generateExpr(expr, context);
		if (last) {
			if (useRetVar) {
				// The returned code may simply be a reference to our retVar, in which case the assignment is obsolete.
				if (retVar != ec.code)
					context.stmts.push_back(retVar + " = " + ec.code + ";");
			} else {
				code = ec;
			}
		} else if (!ec.isRef) {
			context.stmts.push_back(ec.code + ";");
		}
	}

	return code;
}

/**
 * @brief Generates code for the given expression node.
 *
 * The context is populated with all required statements that need to be
 * executed before the returned expression code is valid for use. The resulting
 * ExprCode contains the code required to reference the result of this
 * expression. If the isRef flag is set, the code refers to a symbol that holds
 * the expression's result. Otherwise, the code contains the expression itself
 * and needs to be wrapped in a statement if used inside a block.
 */
CodeGenerator::ExprCode CodeGenerator::generateExpr(const NodePtr& node, BlockContext& context)
{
	if (const VarDefExpr::Ptr& var = VarDefExpr::from(node))
	{
		// Generate a C-flavored name for this variable.
		string name = var->getName() + "_var";
		context.vars[var->getId()] = name;
		context.usedSymbols.insert(name);

		// Generate the statement that declares the variable.
		stringstream stmt;
		stmt << "void* ";
		stmt << name;
		if (const NodePtr& init = var->getInitialExpr(false)) {
			ExprCode c = generateExpr(init, context);
			stmt << " = " << c.code;
		}
		stmt << ";";
		context.stmts.push_back(stmt.str());

		// Return the resulting ExprCode structure.
		ExprCode ec;
		ec.code = name;
		ec.isRef = true;
		ec.precedence = kPrimaryPrec;
		return ec;
	}

	if (const NumberConstExpr::Ptr& num = NumberConstExpr::from(node)) {
		ExprCode ec;
		ec.code = num->getValue();
		ec.isRef = false;
		ec.precedence = kPrimaryPrec;
		return ec;
	}

	if (const AssignmentExpr::Ptr& as = AssignmentExpr::from(node))
	{
		// Only identifier expressions are supported as assignment targets.
		const IdentifierExpr::Ptr& lhs = IdentifierExpr::from(as->getLhs());
		if (!lhs) {
			throw std::runtime_error("Only IdentifierExpr may be used as the lhs of an assignment, got " + as->getLhs()->getClassName() + " instead.");
		}

		// Look up the name that was given to the assignment target.
		const NodeId& id = lhs->getBindingTarget()->getId();
		BlockContext::VarMap::iterator lhs_name_it = context.vars.find(id);
		if (lhs_name_it == context.vars.end()) {
			throw std::runtime_error("Identifier " + lhs->getName() + " is bound to target " + id.str() + " (" + lhs->getBindingTarget()->getClassName() + ") for which no name has been generated.");
		}
		string name = lhs_name_it->second;

		// Generate the assignment.
		ExprCode ec_rhs = generateExpr(as->getRhs(), context);
		ExprCode ec;
		ec.code = name + " = " + precedenceWrapped(ec_rhs, kAssignmentPrec);
		ec.isRef = false;
		ec.precedence = kAssignmentPrec;
		return ec;
	}

	if (const IdentifierExpr::Ptr& ident = IdentifierExpr::from(node))
	{
		const NodeId& id = ident->getBindingTarget()->getId();
		BlockContext::VarMap::iterator name_it = context.vars.find(id);
		if (name_it == context.vars.end()) {
			throw std::runtime_error("Identifier " + ident->getName() + " is bound to target " + id.str() + " (" + ident->getBindingTarget()->getClassName() + ") for which no name has been generated.");
		}
		ExprCode ec;
		ec.code = name_it->second;
		ec.isRef = false;
		ec.precedence = kPrimaryPrec;
		return ec;
	}

	if (CallInterface* call = node->asCall())
	{
		// Find the called function.
		const CallCandidate::Ptr& candidate = CallCandidate::needFrom(call->getSelectedCallCandidate()); // throws if null
		const NodePtr& funcNode = candidate->getFunc();
		CallableInterface* func = funcNode->needCallable();
		const NodeVector& args = call->getCallArgs();

		const FuncType::Ptr& type = FuncType::needFrom(func->getType());
		const NodePtr& typeIn  = type->getIn();
		const NodePtr& typeOut = type->getOut();

		// If the called function is a builtin function, generate specialized code.
		if (const builtin::FuncDef::Ptr& bi = builtin::FuncDef::from(funcNode)) {
			cout << "Generating code for builtin call to \"" << bi->getName() << "\" " << funcNode->getId() << "\n";
			const TupleType::Ptr& tupleIn = TupleType::needFrom(typeIn);
			const string& name = bi->getName();

			// Unary operator
			if (args.size() == 1) {
				CallArgInterface* arg = args[0]->needCallArg();
				ExprCode ec_arg = generateExpr(arg->getExpr(), context);
				ExprCode ec;
				ec.precedence = kPrefixPrec;
				ec.code = name + precedenceWrapped(ec_arg, ec.precedence);
				ec.isRef = false;
				return ec;
			}

			// Binary operator
			else if (args.size() == 2) {
				int p = -1;
				if (name == "==" || name == "!=") p = kEqualityPrec;
				if (name == ">" || name == "<" || name == ">=" || name == "<=") p = kRelationalPrec;
				if (name == "+" || name == "-") p = kAdditivePrec;
				if (name == "*" || name == "/") p = kMultiplicativePrec;
				if (p == -1) {
					throw std::runtime_error("Precedence for builtin binary operator \"" + name + "\" cannot be determined.");
				}

				CallArgInterface* arg_lhs = args[0]->needCallArg();
				CallArgInterface* arg_rhs = args[1]->needCallArg();

				ExprCode ec_lhs = generateExpr(arg_lhs->getExpr(), context);
				ExprCode ec_rhs = generateExpr(arg_rhs->getExpr(), context);
				ExprCode ec;
				ec.precedence = p;
				ec.code = precedenceWrapped(ec_lhs, p) + " " + name + " " + precedenceWrapped(ec_rhs, p);
				ec.isRef = false;
				return ec;
			}

			// Everything else is not supported.
			else {
				stringstream s;
				s << "Specialized code generation for builtin function " << funcNode->getId() << " not supported, as it takes " << args.size() << " input arguments instead of 1 or 2.";
				throw std::runtime_error(s.str());
			}
		}
		else {
			cout << "Generating code for call to " << funcNode->getId() << "\n";
		}
	}

	if (const BlockExpr::Ptr& block = BlockExpr::from(node)) {
		return generateBlock(block, context);
	}

	if (const IfExpr::Ptr& ie = IfExpr::from(node))
	{
		// Generate the temporary variable that will hold the result of the statement.
		string resVar = context.resVar;
		if (resVar.empty()) {
			resVar = makeTmpVar(context);
			context.stmts.push_back("void* " + resVar + ";");
		}

		// Generate code for the condition expression and initiate the if statement.
		ExprCode ec_cond = generateExpr(ie->getCond(), context);
		stringstream stmt;
		stmt << "if (" << ec_cond.code << ")";

		// Generate code for the main body.
		BlockContext context_body(&context);
		context_body.resVar = resVar;
		ExprCode ec_body = generateExpr(ie->getBody(), context_body);

		stmt << " {\n";
		for (BlockContext::Stmts::iterator it = context_body.stmts.begin(); it != context_body.stmts.end(); it++) {
			stmt << "    " << indent(*it) << "\n";
		}
		if (resVar != ec_body.code)
			stmt << "    " << resVar << " = " << ec_body.code << ";\n";
		stmt << "}";

		// Generate code for the else block.
		const NodePtr& elseBlock = ie->getElseExpr(false);
		if (elseBlock) {
			BlockContext context_else(&context);
			context_else.resVar = resVar;
			ExprCode ec_else = generateExpr(elseBlock, context_else);

			stmt << " else {\n";
			for (BlockContext::Stmts::iterator it = context_else.stmts.begin(); it != context_else.stmts.end(); it++) {
				stmt << "    " << indent(*it) << "\n";
			}
			if (resVar != ec_else.code)
				stmt << "    " << resVar << " = " << ec_else.code << ";\n";
			stmt << "}";
		}

		// Add the synthesized statement to the context and wrap the result variable accordingly.
		context.stmts.push_back(stmt.str());
		ExprCode ec;
		ec.code = resVar;
		ec.isRef = true;
		ec.precedence = kPrimaryPrec;
		return ec;
	}

	if (const IfCaseExpr::Ptr& ice = IfCaseExpr::from(node))
	{
		// Generate the temporary variable that will hold the result of the statement.
		string resVar = context.resVar;
		if (resVar.empty()) {
			resVar = makeTmpVar(context);
			context.stmts.push_back("void* " + resVar + ";");
		}

		// Generate the conditional branches of the expression.
		const NodeVector& conds = ice->getConds();
		stringstream stmt;

		for (NodeVector::const_iterator it = conds.begin(); it != conds.end(); it++) {
			const IfCaseExprCond::Ptr& cond = IfCaseExprCond::needFrom(*it);
			bool isFirst = (it == conds.begin());

			// Generate the code for the condition expression.
			ExprCode ec_cond = generateExpr(cond->getCond(), context);
			if (!isFirst) stmt << " else ";
			stmt << "if (" << ec_cond.code << ") {\n";
			
			// Generate the code for the body of the branch.
			BlockContext context_branch(&context);
			context_branch.resVar = resVar;
			ExprCode ec_branch = generateExpr(cond->getExpr(), context_branch);
			for (BlockContext::Stmts::iterator it = context_branch.stmts.begin(); it != context_branch.stmts.end(); it++) {
				stmt << "    " << indent(*it) << "\n";
			}
			if (resVar != ec_branch.code)
				stmt << "    " << resVar << " = " << ec_branch.code << ";\n";
			stmt << "}";
		}

		// Generate the default branch of the expression.
		const NodePtr& otherwise = ice->getOtherwise(false);
		if (otherwise) {
			BlockContext context_otherwise(&context);
			context_otherwise.resVar = resVar;
			ExprCode ec_otherwise = generateExpr(otherwise, context_otherwise);
			stmt << " else {\n";
			for (BlockContext::Stmts::iterator it = context_otherwise.stmts.begin(); it != context_otherwise.stmts.end(); it++) {
				stmt << "   " << indent(*it) << "\n";
			}
			if (resVar != ec_otherwise.code)
				stmt << "    " << resVar << " = " << ec_otherwise.code << ";\n";
			stmt << "}";
		}

		// Add the synthesized statement to the context and wrap the result variable accordingly.
		context.stmts.push_back(stmt.str());
		ExprCode ec;
		ec.code = resVar;
		ec.isRef = true;
		ec.precedence = kPrimaryPrec;
		return ec;
	}

	if (const ForExpr::Ptr& fex = ForExpr::from(node))
	{
		const NodePtr& init = fex->getInit(false);
		const NodePtr& cond = fex->getCond();
		const NodePtr& step = fex->getStep(false);

		// Generate the temporary variable that will hold the last iteration of the loop.
		string resVar = context.resVar;
		if (resVar.empty()) {
			resVar = makeTmpVar(context);
			context.stmts.push_back("void* " + resVar + ";");
		}

		// Generate the code for the initial expression and initialize the statement.
		stringstream stmt;
		stmt << "for (";
		if (init) {
			ExprCode ec_init = generateExpr(init, context);
			if (!ec_init.isRef)
				stmt << ec_init.code;
		}
		stmt << ";";

		// Generate the code for the condition expression in a separate block
		// context. If context_body contains any statements after the condition
		// expression has been generated, the condition needs to be checked
		// inside the body of the loop, instead of pasting the expression code
		// into the for statement itself.
		BlockContext context_body(&context);
		ExprCode ec_cond = generateExpr(cond, context_body);

		bool complexCond = !context_body.stmts.empty();
		if (complexCond) {
			stmt << ";"; // no explicit condition in the for statement
			context_body.stmts.push_back("if (!" + precedenceWrapped(ec_cond, kPrefixPrec) + ") break;");
		} else {
			stmt << " " << ec_cond.code << ";";
		}

		// Generate the code for the loop body itself.
		context_body.resVar = resVar;
		ExprCode ec_body = generateExpr(fex->getBody(), context_body);
		context_body.resVar.clear();
		if (!ec_body.isRef)
			context_body.stmts.push_back(ec_body.code + ";");

		// Generate the code for the step instruction. If the step expression
		// code introduced new statements into context_body, the step statement
		// is moved into the loop body instead of keeping it in the for
		// statement.
		if (step) {
			int size = context_body.stmts.size();
			ExprCode ec_step = generateExpr(step, context_body);
			if (size == context_body.stmts.size()) {
				stmt << " " << ec_step.code;
			} else {
				context_body.stmts.push_back(ec_step.code + ";");
			}
		}

		// Synthesize the body of the for loop.
		stmt << ") {\n";
		for (BlockContext::Stmts::iterator it = context_body.stmts.begin(); it != context_body.stmts.end(); it++) {
			stmt << "    " << indent(*it) << "\n";
		}
		stmt << "}";

		// Generate the output code structure.
		context.stmts.push_back(stmt.str());
		ExprCode ec;
		ec.isRef = true;
		ec.code = resVar;
		ec.precedence = kPrimaryPrec;
		return ec;
	}

	// If we get to this location, the expression could not be converted to C code.
	throw std::runtime_error("Code for expression " + node->getClassName() + " cannot be generated.");
}

/**
 * @brief Returns an indented version of the input string.
 *
 * This function basically puts a couple of spaces after each newline character.
 */
string CodeGenerator::indent(const string& in)
{
	string out;
	for (string::const_iterator it = in.begin(); it != in.end(); it++) {
		out += *it;
		if (*it == '\n')
			out += "    ";
	}
	return out;
}

/**
 * @brief Generates a new temporary variable name.
 *
 * The variable name is added to the context's usedSymbols vector and the name
 * is returned.
 */
string CodeGenerator::makeTmpVar(BlockContext& context)
{
	string name;
	do {
		stringstream s;
		s << "tmp" << context.tmpIndex++;
		name = s.str();
	} while (context.usedSymbols.count(name));
	context.usedSymbols.insert(name);
	return name;
}

/**
 * @brief Wraps the given string in paranthesis if needed.
 *
 * If prec is larger or equal to the outer_prec, the given string is returned
 * with surrounding paranthesis. Otherwise the unmodified string is returned.
 * This allows for automated precedence wrapping.
 */
string CodeGenerator::precedenceWrapped(const string& s, int prec, int outer_prec)
{
	if (prec >= outer_prec)
		return "(" + s + ")";
	else
		return s;
}

/**
 * @brief Wraps the given expression code in paranthesis if needed.
 *
 * Calls precedenceWrapped() with the ExprCode's code and precedence as
 * arguments.
 */
string CodeGenerator::precedenceWrapped(const ExprCode& ec, int outer_prec)
{
	return precedenceWrapped(ec.code, ec.precedence, outer_prec);
}