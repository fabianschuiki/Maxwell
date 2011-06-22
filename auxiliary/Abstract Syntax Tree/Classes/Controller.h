//
//  Controller.h
//  Abstract Syntax Tree
//
//  Created by Fabian Schuiki on 22.06.11.
//  Copyright 2011 Axamblis. All rights reserved.
//

#import <Cocoa/Cocoa.h>


@interface Controller : NSObject <NSTextViewDelegate>
{
	IBOutlet NSTextView * codeView;
	NSAttributedString * tokens;
	NSAttributedString * ast;
	
	NSLock * processLock;
	BOOL isProcessing;
	BOOL shouldProcess;
	
	NSLock * resultsLock;
	struct Tokenizer * tokenizer;
}

@property (copy) NSAttributedString * tokens;
@property (copy) NSAttributedString * ast;

- (void)formatCode;
- (void)formatCodeTokens;

- (void)shouldProcessCode;
- (void)processCodeInBackground;
- (void)processCode;

@end
