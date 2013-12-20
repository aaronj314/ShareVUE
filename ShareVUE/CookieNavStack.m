//
//  CookieNavStack.m
//  ShareVUE
//
//  Created by Aaron Jones on 3/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CookieNavStack.h"
#import "CookieNav.h"

@implementation CookieNavStack

-(void)dealloc {
	[stack release];
	[super dealloc];
}

-(id)init{
	self = [super init];
	if (self != nil) {
		stack = [[NSMutableArray alloc] initWithCapacity:0];
	}
	return self;
}

-(void)push:(CookieNav *)cookie {
	cookie.button.tag = [stack count];
	return [stack addObject:cookie];
}

-(CookieNav *)popToRoot {
    CookieNav *cookie = [[stack objectAtIndex:0] retain];
    for (CookieNav *c in stack) {
        [c.delegate navPop];
    }
	[stack removeAllObjects];
	return [cookie autorelease];
}

-(CookieNav *)pop {
	CookieNav *cookie = [[stack objectAtIndex:[stack count] -1] retain];
	[stack removeObjectAtIndex:[stack count] -1];
	return [cookie autorelease];
}

-(void)clear {
	[stack removeAllObjects];
}

-(NSInteger)count {
	return [stack count];
}
@end
