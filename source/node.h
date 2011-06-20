#pragma once
#include <vector>
#include <string>
#include <sstream>


namespace Maxwell {
	
	class Node {
	public:
		virtual ~Node() {}
		virtual std::string describe(int indent = 0) const = 0;
		std::string pad(int indent) const { return std::string(indent*2, ' '); }
	};
	
	class Statement : public Node {
	};
	
	class Expression : public Node {
	};
	
	typedef std::vector<Statement *> Statements;
	typedef std::vector<Expression *> Expressions;
	
	
	
	class Identifier : public Expression {
	public:
		std::string name;
		Identifier() {}
		Identifier(const std::string & name) : name(name) {}
		virtual std::string describe(int indent = 0) const { return pad(indent) + name; }
	};
	
	typedef std::vector<Identifier *> Identifiers;
	
	
	
	/* A block groups a bunch of statements together in curly braces. */
	class Block : public Expression {
	public:
		Statements statements;
		
		virtual std::string describe(int indent = 0) const {
			std::stringstream s;
			std::string pad0 = pad(indent);
			s << pad0 << "{" << std::endl;
			for (int i = 0; i < statements.size(); i++)
				s << statements[i]->describe(indent + 1);
			s << pad0 << "}" << std::endl;
			return s.str();
		}
	};
	
	class ClassDefinition : public Statement {
	public:
		Identifier name;
		Identifier super;
		Identifiers interfaces;
		
		virtual std::string describe(int indent = 0) const {
			std::stringstream s;
			s << pad(indent) << "class " << name.describe();
			if (!super.name.empty())
				s << " : " << super.describe();
			if (!interfaces.empty()) {
				s << " <";
				int i;
				for (i = 0; i < interfaces.size(); i++) {
					if (i > 0) s << ", ";
					s << interfaces[i]->name;
				}
				s << ">";
			}
			s << std::endl;
			return s.str();
		}
	};
}
