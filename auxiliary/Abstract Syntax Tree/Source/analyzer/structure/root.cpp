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
	//List of all possible nodes.
	node(root_stmt);
    node(expr);
    node(op_binary); node(op_unary);
	
	/*** Root node ***/
	fork() many(ref(root_stmt));
	
	/*** Root Statement ***/
	(*root_stmt)
	.fork() ref(expr) SEMICOLON safe
	;
    
    /*** Expression ***/
    (*expr)
    .fork() numeric
    .fork() ident
    .fork() LPAREN ref(expr) RPAREN
    .fork() ref(expr) ref(op_binary) ref(expr)
    .fork() ref(expr) DOT ident
    ;
    
    /*** Operators ***/
    (*op_binary)
    .fork() PLUS
    .fork() MINUS
    .fork() ASTERISK
    .fork() FSLASH
    ;
}

StructureRoot::~StructureRoot()
{
	for (std::vector<StructureNode *>::iterator n = nodes.begin(); n != nodes.end(); n++)
		delete *n;
	nodes.clear();
}
