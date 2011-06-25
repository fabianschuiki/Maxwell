#include "root.h"

#define node(n)	StructureNode * n = new StructureNode(#n); nodes.push_back(n)
#define key(k)	.add(new StructureToken(StructureToken::Keyword, k))
#define ident	.add(new StructureToken(StructureToken::Identifier))
#define sym(s)	.add(new StructureToken(StructureToken::Symbol, s))
#define ref(r)	.add(new StructureToken(StructureToken::Reference, r))
#define opt(x)	.opt()x.done()
#define many(x)	.many()x.done()

#define SEMICOLON	sym(";")
#define COLON		sym(":")
#define COMMA		sym(",")
#define DOT			sym(".")
#define LT	sym("<")
#define GT	sym(">")


StructureRoot::StructureRoot() : StructureNode("root")
{
	//Introduce all possible nodes.
	node(root_stmt);
	node(class_proto);
	
	//The root node accepts an arbitrary amount of root statements.
	fork() many(ref(root_stmt));
	
	/*** Root Statement ***/
	(*root_stmt)
	.fork() ref(class_proto) SEMICOLON
	;
	
	/*** Classes ***/
	//Prototype
	(*class_proto)
	.fork() key("class") ident opt(COLON ident) opt(LT ident many(COMMA ident) GT)
	;
}

StructureRoot::~StructureRoot()
{
	for (std::vector<StructureNode *>::iterator n = nodes.begin(); n != nodes.end(); n++)
		delete *n;
	nodes.clear();
}
