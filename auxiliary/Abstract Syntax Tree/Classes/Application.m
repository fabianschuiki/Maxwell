//
//  Application.m
//  Abstract Syntax Tree
//
//  Created by Fabian Schuiki on 22.06.11.
//  Copyright 2011 Axamblis. All rights reserved.
//

#import "Application.h"


@implementation Application

- (void)finishLaunching
{
	[super finishLaunching];
	NSURL * url = [[NSUserDefaults standardUserDefaults] URLForKey:@"LastDocument"];
	if (url)
		[[NSDocumentController sharedDocumentController] openDocumentWithContentsOfURL:url display:YES error:NULL];
}

@end
