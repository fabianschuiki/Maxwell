#include <vector>


namespace Lexer {
	
	struct Node {
		enum Type {
			TypeGroup,
		};
		const Type type;
		Node(Type t) : type(t) {}
	};
	
	struct Group : public Node {
		std::vector<Node *> children;
		Group() : Node(TypeGroup) {}
	};
}
