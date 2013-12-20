//
//  cookieNavUIViewController.m
//  ShareVUE
//
//  Created by Darren Mason on 2/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CookieNav.h"


@implementation CookieNav
@synthesize cookieLabel;
@synthesize detail;
@synthesize main;
@synthesize master;
@synthesize button;
@synthesize delegate;
@synthesize masterBeforeDetail;

- (void)dealloc {
    [main release];
    [delegate release];
	[cookieLabel release];
	[detail release];
	[master release];
	[button release];
    [super dealloc];
}

@end
