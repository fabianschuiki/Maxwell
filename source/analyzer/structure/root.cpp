#include "root.h"

#define node(n)	StructureNode * n = new StructureNode(#n); nodes.push_back(n)
#define key(k)	.add(new StructureToken(StructureToken::Keyword, k))
#define ident	.add(new StructureToken(StructureToken::Identifier))
#define numeric	.add(new StructureToken(StructureToken::Numeric))
#define string	.add(new StructureToken(StructureToken::String))
#define sym(s)	.add(new StructureToken(StructureToken::Symbol, s))
#define ref(r)	.add(new StructureToken(StructureToken::Reference, r))
#define opt(x)	.opt()x.done()
#define many(x)	.many()x.done()
#define safe	.safe()

#define SEMICOLON	sym(";")
#define COLON		sym(":")
#define COMMA		sym(",")
#define DOT			sym(".")
#define EQUAL		sym("=")

//Binary Operators
#define PLUS		sym("+")
#define MINUS		sym("-")
#define ASTERISK	sym("*")
#define FSLASH		sym("/")

//Compare Operators
#define CLT	sym("<")
#define CLE	sym("<=")
#define CGE	sym(">=")
#define CGT	sym(">")

//Grouping
#define LPAREN	sym("(")
#define RPAREN	sym(")")
#define LBRACE	sym("{")
#define RBRACE	sym("}")
#define LBRACK	sym("[")
#define RBRACH	sym("]")


StructureRoot::StructureRoot() : StructureNode("root")
{
	//Introduce all possible nodes.
	node(root_stmt);
	node(class_decl); node(class_def); node(class_stmt);
	node(func_decl); node(func_def); node(func_shared); node(func_args); node(func_arg);
	node(func_stmt);
	node(var_decl); node(var_def);
	node(type);
	node(expr);
	
	//The root node accepts an arbitrary amount of root statements.
	fork() many(ref(root_stmt));
	
	/*** Root Statement ***/
	/* Only class declarations and definitions as well as some import commands are allowed at root
	 * level. */
	(*root_stmt)
	.fork() ref(class_decl) SEMICOLON safe
	.fork() ref(class_def)
	;
}

StructureRoot::~StructureRoot()
{
	for (std::vector<StructureNode *>::iterator n = nodes.begin(); n != nodes.end(); n++)
		delete *n;
	nodes.clear();
}
