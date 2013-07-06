/* Copyright © 2013 Fabian Schuiki */
#include "Serializer.hpp"
#include "Node.hpp"

using ast::Serializer;
using ast::Node;
using std::string;
using std::ostream;
using boost::shared_ptr;

void Serializer::encode(ostream& out, const shared_ptr<Node>& node)
{

}

string Serializer::encode(const shared_ptr<Node>& node)
{
	return "";
}