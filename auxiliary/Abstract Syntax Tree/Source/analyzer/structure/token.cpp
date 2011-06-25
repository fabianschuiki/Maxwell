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
	group = None;
}



StructureToken::operator std::string ()
{
	std::stringstream out;
	if (group == Many) out << "*{";
	if (group == Optional) out << "?{";
	switch (type) {
		case Identifier:	out << "<ident>"; break;
		case Numeric:		out << "<num>"; break;
		case String:		out << "<string>"; break;
			
		case Keyword:		out << /*"\"" <<*/ text /*<< "\""*/; break;
		case Symbol:		out << /*"'" <<*/ text /*<< "'"*/; break;
			
		case Reference:		out << (reference ? reference->getName() : "???"); break;
			
	}
	//if (safe) out << "•";
	if (group == Done) out << "}";
	return out.str();
}

bool StructureToken::dontMatch() const
{
	return (type == Empty || type == Reference);
}
