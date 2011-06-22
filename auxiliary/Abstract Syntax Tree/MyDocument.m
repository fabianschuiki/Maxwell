//
//  MyDocument.m
//  Abstract Syntax Tree
//
//  Created by Fabian Schuiki on 22.06.11.
//  Copyright 2011 Axamblis. All rights reserved.
//

#import "MyDocument.h"

@implementation MyDocument

@synthesize tokens, ast;


- (id)init
{
    self = [super init];
    if (self) {
    
        // Add your subclass-specific initialization here.
        // If an error occurs here, send a [self release] message and return nil.
    
    }
    return self;
}

- (NSString *)windowNibName
{
    // Override returning the nib file name of the document
    // If you need to use a subclass of NSWindowController or if your document supports multiple NSWindowControllers, you should remove this method and override -makeWindowControllers instead.
    return @"MyDocument";
}

- (void)windowControllerDidLoadNib:(NSWindowController *) aController
{
    [super windowControllerDidLoadNib:aController];
    // Add any code here that needs to be executed once the windowController has loaded the document's window.
	[codeView setDelegate:self];
	if (loadedCode) {
		[[codeView textStorage] setAttributedString:loadedCode];
		[loadedCode autorelease]; loadedCode = nil;
	}
	[self formatCode];
	[[aController window] zoom:nil];
}

- (NSData *)dataOfType:(NSString *)typeName error:(NSError **)outError
{
	return [[[codeView textStorage] string] dataUsingEncoding:NSUTF8StringEncoding];
}

- (BOOL)readFromData:(NSData *)data ofType:(NSString *)typeName error:(NSError **)outError
{
	NSString * string = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
	loadedCode = [[NSAttributedString alloc] initWithString:string];
    return YES;
}

- (void)setFileURL:(NSURL *)absoluteURL
{
	[super setFileURL:absoluteURL];
	[[NSUserDefaults standardUserDefaults] setURL:absoluteURL forKey:@"LastDocument"];
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

- (void)textViewDidChangeSelection:(NSNotification *)notification
{
	NSLog(@"text changed!");
}

@end
