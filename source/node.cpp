#include "node.h"

using namespace Maxwell;



std::string TextualExpression::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent);
	s << name;
	if (indent > 0) s << ";" << std::endl;
	return s.str();
}

std::string String::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent);
	s << "\"" << TextualExpression::describe() << "\"";
	if (indent > 0) s << ";" << std::endl;
	return s.str();
}



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
	s << pad(indent) << "CLASS " << name->describe();
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
	s << pad(indent) << (shared ? "+" : "-");
	if (returnType)
		s << " " << returnType->describe();
	if (arguments) {
		int i;
		for (i = 0; i < arguments->size(); i++)
			s << " " << (*arguments)[i]->describe();
	}
	if (statements)
		s << std::endl << statements->describe(indent);
	else
		s << ";" << std::endl;
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
	s << pad(indent) << "VAR";
	if (type) s << " " << type->describe();
	if (name) s << " " << name->describe();
	if (initial) s << " = " << initial->describe();
	if (indent > 0) s << ";" << std::endl;
	return s.str();
}



std::string Tuple::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent) << "TUPLE(";
	if (expressions) {
		int i;
		for (i = 0; i < expressions->size(); i++) {
			if (i > 0) s << ", ";
			s << (*expressions)[i]->describe();
		}
	}
	s << ")";
	return s.str();
}

std::string MemberAccess::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent);
	s << subject->describe() << "." << member->describe();
	if (indent > 0) s << ";" << std::endl;
	return s.str();
}

std::string FunctionCall::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent);
	if (receiver) s << receiver->describe();
	s << ":";
	if (arguments) {
		if (!arguments->empty()) s << "(";
		for (int i = 0; i < arguments->size(); i++) {
			if (i > 0) s << " ";
			s << (*arguments)[i]->describe();
		}
		if (!arguments->empty()) s << ")";
	}
	if (indent > 0) s << ";" << std::endl;
	return s.str();
}

std::string FunctionCallArgument::describe(int indent) const
{
	std::stringstream s;
	s << pad(indent);
	s << name->describe();
	if (argument) s << ":" << argument->describe();
	return s.str();
}
