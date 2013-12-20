//
//  CookieNavStack.h
//  ShareVUE
//
//  Created by Aaron Jones on 3/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class CookieNav;

@interface CookieNavStack : NSObject {
	NSMutableArray *stack;
}

-(void)push:(CookieNav *)object;
-(CookieNav *)pop;
-(CookieNav *)popToRoot;
-(void)clear;
-(NSInteger)count;
@end
