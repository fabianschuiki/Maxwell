//
//  Controller.mm
//  Abstract Syntax Tree
//
//  Created by Fabian Schuiki on 22.06.11.
//  Copyright 2011 Axamblis. All rights reserved.
//

#import "Controller.h"


@implementation Controller

@synthesize tokens, ast;


- (void)awakeFromNib
{
	[codeView setDelegate:self];
}

- (void)formatCode
{
	NSMutableAttributedString * s = [codeView textStorage];
	
	//Basically reset to white.
	NSDictionary * attrs = [NSDictionary dictionaryWithObjectsAndKeys:
							[NSColor whiteColor], NSForegroundColorAttributeName,
							[NSFont fontWithName:@"Menlo" size:11], NSFontAttributeName,
							nil];
	[s setAttributes:attrs range:NSMakeRange(0, [[s string] length])];
}

- (void)textDidChange:(NSNotification *)notification
{
	NSLog(@"text changed!");
}

@end
