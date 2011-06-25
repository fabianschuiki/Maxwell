#include <sstream>
#include "token.h"
#include "node.h"


StructureToken::StructureToken(Type t)
: type(t), reference(NULL) { init(); }
StructureToken::StructureToken(Type t, const std::string & txt)
: type(t), reference(NULL), text(txt) { init(); }
StructureToken::StructureToken(Type t, StructureNode * r)
: type(t), reference(r) { init(); }

void StructureToken::init()
{
	safe = false;
}



StructureToken::operator std::string ()
{
	std::stringstream out;
	switch (type) {
		case Identifier:	out << "<ident>"; break;
		case Numeric:		out << "<num>"; break;
		case String:		out << "<string>"; break;
			
		case Keyword:		out << /*"\"" <<*/ text /*<< "\""*/; break;
		case Symbol:		out << /*"'" <<*/ text /*<< "'"*/; break;
			
		case Reference:		out << (reference ? reference->getName() : "???"); break;
			
		case Optional:		out << "?{"; break;
		case Many:			out << "*{"; break;
		case Done:			out << "}"; break;
			
	}
	//if (safe) out << "•";
	return out.str();
}

bool StructureToken::dontMatch() const
{
	return (type == Empty || type == Reference || isBranch());
}

bool StructureToken::isBranch() const
{
	return (type >= Optional);
}
