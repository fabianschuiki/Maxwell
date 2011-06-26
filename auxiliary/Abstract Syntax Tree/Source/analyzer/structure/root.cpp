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

#define SEMICOLON	sym(";")
#define COLON		sym(":")
#define COMMA		sym(",")
#define DOT			sym(".")
#define EQUAL		sym("=")

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
	node(var_decl); node(var_def);
	node(expr);
	
	//The root node accepts an arbitrary amount of root statements.
	fork() many(ref(root_stmt));
	
	/*** Root Statement ***/
	/* Only class declarations and definitions as well as some import commands are allowed at root
	 * level. */
	(*root_stmt)
	.fork() ref(class_decl) SEMICOLON
	.fork() ref(class_def)
	;
	
	
	
	/*** Classes ***/
	/* A class declaration consists of the keyword "class" followed by the class named, optionally
	 * followed by a colon and the superclass, optionally followed by a list of interfaces. */
	(*class_decl)
	.fork() key("class") ident opt(COLON ident) opt(CLT ident many(COMMA ident) CGT);
	
	/* A class definition consists of a class declaration followed by curly braces and an arbitrary
	 * number of class statements. */
	(*class_def)
	.fork() ref(class_decl) LBRACE many(ref(class_stmt)) RBRACE;
	
	/* A class statement can be a variable definition or a function declaration/definition. */
	(*class_stmt)
	.fork() ref(var_def) SEMICOLON;
	
	
	
	/*** Variables ***/
	/* A variable declaration consists of the variable type, a list of qualifiers and the variable
	 * name. */
	(*var_decl)
	.fork() ident ident;
	
	/* A variable definition is a variable declaration optionally followed by an initial
	 * assignment. */
	(*var_def)
	.fork() ref(var_decl) opt(EQUAL ref(expr));
	
	
	
	/*** Expressions ***/
	(*expr)
	//Basics
	.fork() ident
	.fork() numeric
	.fork() string
	.fork() LPAREN ref(expr) RPAREN
	//Tuple
	.fork() LPAREN ref(expr) COMMA ref(expr) many(COMMA ref(expr)) RPAREN
	//Member access
	.fork() ref(expr) DOT ident
	;
}

StructureRoot::~StructureRoot()
{
	for (std::vector<StructureNode *>::iterator n = nodes.begin(); n != nodes.end(); n++)
		delete *n;
	nodes.clear();
}
