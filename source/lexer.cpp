#include <iostream>
#include <sstream>
#include <stack>
#include "lexer.h"
using namespace Lexer;


Node * Node::make(Type type, const std::string & text, const Range & range)
{
	//Allocate a new node accordingly.
	Node * node = NULL;
	switch (type) {
		case kSymbol: {
			
			//Check whether this symbol starts a new group.
			Group::Subtype gst = Group::subtypeForOpeningSymbol(text);
			if (gst != Group::kInvalidGroup)
				node = new Group(gst);
		} break;
	}
	if (!node && type != kInvalid)
		node = new Node(type);
	
	//Apply the basic attributes to the node.
	if (node) {
		node->text = text;
		node->range = range;
	}
	return node;
}

Node::Node(Type t) : type(t)
{
	next = NULL;
}

Node::~Node()
{
	if (next) {
		delete next;
		next = NULL;
	}
}

bool Node::isIdentifier(const std::string & name) const
{
	return (type == kIdentifier && (name.empty() || text == name));
}

bool Node::isSymbol(const std::string & name) const
{
	return (type == kSymbol && (name.empty() || text == name));
}

bool Node::isGroup() const
{
	return (type == kGroup);
}

std::string Node::describe(int depth, int indent)
{
	return text;
}


Group::Group(Subtype s) : Node(kGroup), subtype(s)
{
	firstChild = NULL;
	lastChild = NULL;
}

Group::~Group()
{
	if (firstChild) {
		delete firstChild;
		firstChild = NULL;
	}
	lastChild = NULL;
}

void Group::addChild(Node * c)
{
	if (!c) return;
	if (lastChild)
		lastChild->next = c;
	lastChild = c;
	if (!firstChild)
		firstChild = lastChild;
}

const std::string Group::getOpeningSymbol()
{
	switch (subtype) {
		case kBrackets: return "["; break;
		case kBraces: return "{"; break;
		case kParanthesis: return "("; break;
	}
	return "";
}

const std::string Group::getClosingSymbol()
{
	switch (subtype) {
		case kBrackets: return "]"; break;
		case kBraces: return "}"; break;
		case kParanthesis: return ")"; break;
	}
	return "";
}

Group::Subtype Group::subtypeForOpeningSymbol(const std::string & os)
{
	if (os == "[") return kBrackets;
	if (os == "{") return kBraces;
	if (os == "(") return kParanthesis;
	return kInvalidGroup;
}

std::string Group::describe(int depth, int indent)
{
	std::string brk = "\n";
	brk += std::string(indent * 4, ' ');
	std::stringstream s;
	s << getOpeningSymbol();
	if (subtype == kBraces && depth != 0)
		s << brk;
	if (depth != 0) {
		Node * c = firstChild;
		bool first = true;
		while (c) {
			if (!first)
				s << " ";
			first = false;
			s << c->describe((depth > 0 ? depth - 1 : depth), indent + 1);
			if (c->type == Node::kSymbol && c->text == ";") {
				s << brk;
				first = true;
			}
			c = c->next;
		}
	} else {
		s << " ... ";
	}
	s << getClosingSymbol();
	return s.str();
}


Identifier::Identifier() : Node(kIdentifier) {}


//These are ranges depicting symbols.
const static struct { int s; int e; } symbolRanges[] = {
	{0x21, 0x2F},
	{0x3A, 0x3F},
	{0x5B, 0x5E},
	{0x7B, 0x7E},
	{0, 0}
};

//These are valid combinations of multiple symbols.
const static char * symbolCombinations[] = {
	"=>",
	NULL
};


/** Parses the given input stream and returns the root group node containing the
 * parsed nodes. */
Group * Lexer::parse(std::istream * input)
{
	//Allocate the root group node.
	Group * root = new Group(Group::kRoot);
	
	//Create the group stack so we can have nested nodes.
	std::stack<Group *> groupStack;
	groupStack.push(root);
	
	//We need to keep track of the context we're currently in, since each
	//requries some different form of processing.
	enum Context {
		kCodeContext,
		kSingleLineCommentContext,
		kMultiLineCommentContext,
		kStringContext,
	} context = kCodeContext;
	
	//We need to keep a string around so we can buffer up the characters and
	//keep track of what we are expecting to read.
	Node::Type bufferType = Node::kInvalid;
	Range bufferRange;
	std::string buffer;
	
	//Keep track of the location within the file.
	Location loc;
	
	//Read the input character by character until nothing is left.
	int pc = 0, ppc = 0;
	while (!input->eof()) {
		int c = input->get();
		
		//Advance the location tracker.
		if (c == '\n') {
			loc.line++;
			loc.col = 0;
		}
		
		//Process the character based on the current context.
		Node::Type newBufferType = Node::kInvalid;
		bool wrapUpAnyway = false;
		switch (context) {
				
			//Inside normal code.
			case kCodeContext: {
				
				//Check for comments.
				if (c == '/' && input->peek() == '/') {
					context = kSingleLineCommentContext;
					break;
				}
				if (c == '/' && input->peek() == '*') {
					context = kMultiLineCommentContext;
					break;
				}
				
				//Check for strings.
				if (c == '"') {
					context = kStringContext;
					break;
				}
				
				//Check for symbols.
				bool isSymbol = false;
				for (int i = 0; symbolRanges[i].s != 0; i++) {
					if (c >= symbolRanges[i].s && c <= symbolRanges[i].e) {
						isSymbol = true;
						break;
					}
				}
				if (isSymbol) {
					//Check whether the character can be combined with what's
					//already in the buffer.
					newBufferType = Node::kSymbol;
					std::string lookaheadBuffer = buffer;
					lookaheadBuffer += c;
					wrapUpAnyway = true;
					for (int i = 0; symbolCombinations[i] != 0; i++) {
						if (lookaheadBuffer == symbolCombinations[i]) {
							wrapUpAnyway = false;
							break;
						}
					}
					break;
				}
				
				//Check for numbers.
				if (c >= 0x30 && c <= 0x39) {
					newBufferType =  Node::kNumeric;
					break;
				}
				
				//Check for an identifier, which basically is anything except
				//the above and whitespaces.
				if (c > 0 && c != '\n' && c != '\t' && c != ' ' && c != '\r') {
					newBufferType = Node::kIdentifier;
					break;
				}
			} break;
				
			//Inside comments.
			case kSingleLineCommentContext: {
				if (c == '\n')
					context = kCodeContext;
			} break;
				
			case kMultiLineCommentContext: {
				if (c == '/' && pc == '*')
					context = kCodeContext;
			} break;
			
			//Inside strings.
			case kStringContext: {
				//Check whether we've reached the end of the string in which
				//case we switch back to code context, leaving the kind invalid
				//which will cause the token to be wrapped up.
				if (c == '"' && pc != '\\' && ppc != '\\')
					context = kCodeContext;
				
				//Otherwise we mark this character as part of a string token.
				else if (c > 0)
					newBufferType = Node::kString;
			} break;
		}
		
		//Rotate the character archive.
		ppc = pc;
		pc = c;
		
		//Numeric tokens are allowed in an identifier buffer.
		if (bufferType == Node::kIdentifier &&
			newBufferType == Node::kNumeric)
			newBufferType = bufferType;
		
		//Numeric buffers suck up all identifier and some symbol tokens, since
		//the value's validity is checked at a later stage.
		if (bufferType == Node::kNumeric) {
			if (newBufferType == Node::kIdentifier || c == '.') {
				newBufferType = bufferType;
				wrapUpAnyway = false;
			}
		}
		
		//If the buffer type and this token tpye disagree, wrap up the current
		//buffer.
		if ((bufferType != newBufferType || wrapUpAnyway) && !buffer.empty()) {
			
			//If the current token is a symbol and it closes the topmost group,
			//remove the group from the stack and ignore the symbol.
			if (bufferType == Node::kSymbol &&
				groupStack.top()->getClosingSymbol() == buffer) {
				groupStack.pop();
			} else {
				
				//Create a new node with the buffer content.
				Node * n = Node::make(bufferType, buffer, bufferRange);
				if (n) {
					
					//Add the node to the topmost group.
					groupStack.top()->addChild(n);
					
					//If the returned node is a group node, add it to the top of the
					//group stack so its subnodes get added to it.
					if (n->type == Node::kGroup)
						groupStack.push((Group *)n);
				}
			}
				
			//Clear the buffer and buffer kind.
			buffer.clear();
			bufferType = Node::kInvalid;
		}
		
		//If the current token is valid, set it as the current buffer kind and
		//move the character into the buffer.
		if (newBufferType != Node::kInvalid) {
			if (bufferType == Node::kInvalid)
				bufferRange.start = loc;
			bufferType = newBufferType;
			buffer += c;
		}
		
		//Increase the column counter.
		loc.col++;
		loc.offset++;
		
		//Adjust the buffer range's end now, so that the character we've read is
		//also counted in.
		bufferRange.end = loc;
	}
	
	//Return the root group.
	return root;
}
