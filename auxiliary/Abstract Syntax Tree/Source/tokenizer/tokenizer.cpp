#include <iostream>
#include "tokenizer.h"


const static struct { int s; int e; } symbolRanges[] = {
	{0x21, 0x2F},
	{0x3A, 0x3F},
	{0x5B, 0x5E},
	{0x7B, 0x7E},
	{0, 0}
};

const static char * symbolCombinations[] = {
	"+=", "-=", "*=", "/=",
	"==", "!=", ">=", "<=",
	NULL
};



void Tokenizer::addToken(Token * token)
{
	if (lastToken)
		lastToken->next = token;
	lastToken = token;
	if (!firstToken)
		firstToken = lastToken;
}



Token * Tokenizer::getFirstToken()
{
	return firstToken;
}



Tokenizer::Tokenizer()
{
	firstToken = NULL;
	lastToken = NULL;
}

Tokenizer::~Tokenizer()
{
	if (firstToken)
		delete firstToken;
}



void Tokenizer::process(std::istream & input)
{
	//Clear the current tokens.
	lastToken = NULL;
	if (firstToken)
		delete firstToken;
	firstToken = NULL;
	
	//We need to keep track of the context we're currently in, since each requries some different
	//form of processing.
	enum Context {
		kCodeContext,
		kSingleLineCommentContext,
		kMultiLineCommentContext,
		kStringContext
	} context = kCodeContext;
	
	//We need to keep a string around so we can buffer up the characters and keep track of what we
	//are expecting to read.
	Token::Kind bufferKind = Token::kInvalidToken;
	Range bufferRange;
	std::string buffer;
	
	//Keep track of the location within the file.
	Location loc;
	
	//Read the input character by character until nothing is left.
	int pc = 0, ppc = 0;
	while (!input.eof()) {
		int c = input.get();
		
		//Advance the location tracker.
		if (c == '\n') {
			loc.line++;
			loc.col = 0;
		}
		
		//Process the character based on the current context.
		Token::Kind kind = Token::kInvalidToken;
		bool wrapUpAnyway = false;
		
		switch (context) {
			case kCodeContext: {
				//Check for comments.
				if (c == '/' && input.peek() == '/') {
					context = kSingleLineCommentContext;
					break;
				}
				if (c == '/' && input.peek() == '*') {
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
					//Check whether the character can be combined with what's already in the buffer.
					kind = Token::kSymbolToken;
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
					kind = Token::kNumericToken;
					break;
				}
				
				//Check for an identifier, which basically is anything except the above and white-
				//spaces.
				if (c > 0 && c != '\n' && c != '\t' && c != ' ' && c != '\r') {
					kind = Token::kIdentifierToken;
					break;
				}
			} break;
				
			case kSingleLineCommentContext: {
				if (c == '\n')
					context = kCodeContext;
			} break;
				
			case kMultiLineCommentContext: {
				if (c == '/' && pc == '*')
					context = kCodeContext;
			} break;
				
			case kStringContext: {
				//Check whether we've reached the end of the string in which case we switch back to
				//code context, leaving the kind invalid which will cause the token to be wrapped
				//up.
				if (c == '"' && pc != '\\' && ppc != '\\')
					context = kCodeContext;
				
				//Otherwise we mark this character as part of a string token.
				else if (c > 0)
					kind = Token::kStringToken;
			} break;
		}
		
		//Rotate the character archive.
		ppc = pc;
		pc = c;
		
		//Numeric tokens are allowed in an identifier buffer.
		if (bufferKind == Token::kIdentifierToken && kind == Token::kNumericToken)
			kind = bufferKind;
		
		//Numeric buffers suck up all identifier and some symbol tokens, since the value's validity
		//is checked at a later stage.
		if (bufferKind == Token::kNumericToken)
			if (kind == Token::kIdentifierToken || buffer == ".")
				kind = bufferKind;
		
		//If the buffer kind and this token kind disagree, wrap up the current buffer.
		if ((bufferKind != kind || wrapUpAnyway) && !buffer.empty()) {
			
			//Create a new token with the buffer content.
			Token * t = new Token(bufferKind, buffer, bufferRange);
			addToken(t);
			
			//Clear the buffer and buffer kind.
			buffer.clear();
			bufferKind = Token::kInvalidToken;
		}
		
		//If the current token is valid, set it as the current buffer kind and move the character
		//into the buffer.
		if (kind != Token::kInvalidToken) {
			if (bufferKind == Token::kInvalidToken)
				bufferRange.start = loc;
			bufferKind = kind;
			buffer += c;
		}
		
		//Increase the column counter.
		loc.col++;
		loc.offset++;
		
		//Adjust the buffer range's end now, so that the character we've read is also counted in.
		bufferRange.end = loc;
	}
}
