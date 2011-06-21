#include "node.h"

using namespace Maxwell;


std::string Block::describe(int indent) const
{
	std::stringstream s;
	std::string pad0 = pad(indent);
	s << pad0 << "{" << std::endl;
	for (int i = 0; i < statements.size(); i++)
		s << statements[i]->describe(indent + 1);
	s << pad0 << "}" << std::endl;
	return s.str();
}




std::string ClassDefinition::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent) << "class " << name->describe();
	if (super)
		s << " : " << super->describe();
	if (interfaces) {
		s << " <";
		int i;
		for (i = 0; i < interfaces->size(); i++) {
			if (i > 0) s << ", ";
			s << (*interfaces)[i]->describe();
		}
		s << ">";
	}
	s << std::endl;
	if (statements)
		s << statements->describe(indent);
	return s.str();
}



std::string FunctionDefinition::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent) << (shared ? "shared" : "instance");
	if (returnType)
		s << " " << returnType->describe();
	if (arguments) {
		int i;
		for (i = 0; i < arguments->size(); i++)
			s << " " << (*arguments)[i]->describe();
	}
	s << std::endl;
	if (statements)
		s << statements->describe(indent);
	return s.str();
}

std::string FunctionArgument::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent);
	if (name)     s << name->describe();
	if (argument) s << ":(" << argument->describe() << ")";
	return s.str();
}



std::string VariableDefinition::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent);
	if (type) s << type->describe();
	if (name) s << " " << name->describe();
	return s.str();
}



std::string ConcreteType::describe(int indent) const
{
	std::stringstream s;
	if (name) s << pad(indent) << name->describe();
	return s.str();
}

std::string TupleType::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent) << "(";
	if (types) {
		int i;
		for (i = 0; i < types->size(); i++) {
			if (i > 0) s << ", ";
			s << (*types)[i]->describe();
		}
	}
	s << ")";
	return s.str();
}
