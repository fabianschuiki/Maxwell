#include <sstream>
#include "token.h"
#include "node.h"


StructureToken::StructureToken(Type t) : type(t), safe(false) {}
StructureToken::StructureToken(Type t, const std::string & txt) : type(t), text(txt), safe(false) {}
StructureToken::StructureToken(Type t, StructureNode * r) : type(t), reference(r), safe(false) {}

StructureToken::operator std::string ()
{
	std::stringstream out;
	switch (type) {
		case Identifier:	out << "<ident>"; break;
		case Numeric:		out << "<num>"; break;
		case String:		out << "<string>"; break;
			
		case Keyword:		out << "\"" << text << "\""; break;
		case Symbol:		out << "'" << text << "'"; break;
			
		case Reference:		out << (reference ? reference->getName() : "???"); break;
			
	}
	if (safe) out << "•";
	return out.str();
}
