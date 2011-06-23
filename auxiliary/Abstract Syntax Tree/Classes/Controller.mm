//
//  Controller.mm
//  Abstract Syntax Tree
//
//  Created by Fabian Schuiki on 22.06.11.
//  Copyright 2011 Axamblis. All rights reserved.
//

#import "Controller.h"

#include "../Source/tokenizer/tokenizer.h"
#include "../Source/analyzer/analyzer.h"
#include <sstream>


@implementation Controller

@synthesize tokens, ast;


- (void)awakeFromNib
{
	basicAttrs = [[NSDictionary dictionaryWithObjectsAndKeys:
				   [NSColor whiteColor], NSForegroundColorAttributeName,
				   [NSFont fontWithName:@"Menlo" size:11], NSFontAttributeName,
				   nil] retain];
	
	processLock = [[NSLock alloc] init];
	resultsLock = [[NSLock alloc] init];
	[codeView setDelegate:self];
}

- (void)formatCode
{
	//Reset the code to white.
	NSMutableAttributedString * s = [codeView textStorage];
	[s setAttributes:basicAttrs range:NSMakeRange(0, [[s string] length])];
	
	//Format the tokens in the code.
	[self formatCodeTokens];
}

- (void)formatCodeTokens
{
	[resultsLock lock];
	NSMutableAttributedString * s = [codeView textStorage];
	
	//Iterate through the parsed tokens if there are any.
	if (tokenizer) {
		Token * token = tokenizer->getFirstToken();
		while (token) {
			
			//Convert the token location into an NSRange.
			NSRange range = NSMakeRange(token->range.start.offset, token->range.getLength());
			
			//Decide what background color to use for this token.
			NSColor * color = nil;
			switch (token->kind) {
				case Token::kStringToken:		color = [NSColor magentaColor]; break;
				case Token::kIdentifierToken:	color = [NSColor lightGrayColor]; break;
				case Token::kSymbolToken:		color = [NSColor greenColor]; break;
				case Token::kNumericToken:		color = [NSColor cyanColor]; break;
			}
			
			//Apply the color.
			if (color)
				[s addAttribute:NSForegroundColorAttributeName
						  value:color range:range];
			
			//Apply some background color so we can see where the tokens are.
			[s addAttribute:NSBackgroundColorAttributeName
					  value:[NSColor colorWithCalibratedWhite:1 alpha:0.1]
					  range:range];
			
			//Advance to next token.
			token = token->next;
		}
	}
	
	[resultsLock unlock];
}

- (void)textDidChange:(NSNotification *)notification
{
	[self shouldProcessCode];
}

- (void)shouldProcessCode
{
	[processLock lock];
	
	//Set the should process flag so the code gets processed as soon as possible.
	shouldProcess = YES;
	
	//If we're supposed to be processing code but aren't, we kick off the process.
	if (shouldProcess && !isProcessing)
		[self processCodeInBackground];
	
	[processLock unlock];
}

- (void)processCodeInBackground
{
	isProcessing = YES;
	[self performSelectorInBackground:@selector(processCode) withObject:nil];
}

- (void)processCode
{
	NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
	
	//Clear the shouldProcess flag since we're actually doing it. This allows queueing a new
	//processing request while an old one is running.
	[processLock lock];
	shouldProcess = NO;
	[processLock unlock];
	
	//Create an std::istream of the code.
	std::istringstream codeStream([[[codeView textStorage] string] UTF8String]);
	
	//Create a new tokenizer and parse the input.
	Tokenizer * t = new Tokenizer();
	t->process(codeStream);
	
	//Create a new analyzer and analyze the tokens.
	Analyzer * a = new Analyzer();
	a->process(t->getFirstToken());
	
	/*NSString * temp = [NSString stringWithUTF8String:m->temp.c_str()];
	 self.tokens = [[[NSAttributedString alloc] initWithString:temp attributes:basicAttrs] autorelease];*/
	
	//Store the results.
	[resultsLock lock];
	if (tokenizer) delete tokenizer;
	tokenizer = t;
	if (analyzer) delete analyzer;
	analyzer = a;
	[resultsLock unlock];
	
	//We're done, clear the isProcessing flag and restart the processing if requested.
	[processLock lock];
	isProcessing = NO;
	if (shouldProcess)
		[self processCodeInBackground];
	[processLock unlock];
	
	//Do some cleanup work.
	[self performSelectorOnMainThread:@selector(processCodeDone) withObject:nil waitUntilDone:NO];
	
	[pool release];
}

- (void)processCodeDone
{
	[self formatCode];
}

@end
