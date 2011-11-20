#include <string>
#include <vector>


namespace Lexer {
	
	struct Node {
		enum Type {
			TypeGroup,
			TypeIdentifier,
		};
		const Type type;
		Node(Type t);
	};
	
	struct Group : public Node {
		enum Subtype {
			SubtypeRoot,
			SubtypeBrackets,
			SubtypeBraces,
			SubtypeParanthesis,
		};
		const Subtype subtype;
		std::vector<Node *> children;
		Group(Subtype s);
	};
	
	struct Identifier : public Node {
		std::string string;
		Identifier();
	};
	
	Group * parse(std::istream * in);
}
