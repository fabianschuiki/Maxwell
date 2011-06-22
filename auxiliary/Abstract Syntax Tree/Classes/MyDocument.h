//
//  MyDocument.h
//  Abstract Syntax Tree
//
//  Created by Fabian Schuiki on 22.06.11.
//  Copyright 2011 Axamblis. All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Controller.h"


@interface MyDocument : NSDocument
{
	NSAttributedString * loadedCode;
	IBOutlet NSTextView * codeView;
	IBOutlet Controller * controller;
}

@end
