#include <sstream>
#include "token.h"
#include "node.h"


StructureToken::StructureToken(Type t) : type(t) {}
StructureToken::StructureToken(Type t, const std::string & txt) : type(t), text(txt) {}
StructureToken::StructureToken(Type t, StructureNode * r) : type(t), reference(r) {}

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
	return out.str();
}
