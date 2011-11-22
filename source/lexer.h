#include <string>
#include "location.h"

namespace Lexer {
	
	/** Basic node class from which all Lexer tokens and groups inherit. */
	struct Node {
		
		//Node Type
		enum Type {
			kInvalid,
			kGroup,
			kIdentifier,
			kSymbol,
			kNumeric,
			kString,
		};
		const Type type;
		
		//Hierarchy.
		Node * next;
		
		//Content and location.
		std::string text;
		Range range;
		
		//Factory and construction.
		static Node * make(Type type,
		                   const std::string & text,
		                   const Range & range);
		Node(Type t);
		virtual ~Node();
		
		//Description.
		virtual std::string describe(int depth = -1, int indent = 0);
	};
	
	/** Group of nodes. */
	struct Group : public Node {
		
		//Subtype
		enum Subtype {
			kInvalidGroup,
			kRoot,
			kBrackets,
			kBraces,
			kParanthesis,
		};
		const Subtype subtype;
		
		//Hierarchy.
		Node * firstChild;
		Node * lastChild;
		void addChild(Node * c);
		
		//Delimiters.
		const std::string getOpeningSymbol();
		const std::string getClosingSymbol();
		static Subtype subtypeForOpeningSymbol(const std::string & os);
		
		//Construction.
		Group(Subtype s);
		~Group();
		
		//Description.
		std::string describe(int depth = -1, int indent = 0);
	};
	
	/** Identifier Token. This can be anything from typename to keyword. */
	struct Identifier : public Node {
		Identifier();
	};
	
	Group * parse(std::istream * input);
}
