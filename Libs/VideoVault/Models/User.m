//
//  User.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "User.h"
#import "Project.h"

@implementation User
@synthesize userId, userName, groupId, roleId, fullName;
@synthesize token;
@synthesize projects;

+(User *)userForDemo {
	User *u = [[[User alloc] init] autorelease];
	u.userName = @"Demo User";
	u.projects = [Project projectsForDemo];
	return u;
}

- (void) dealloc
{
	NSLog(@"dealloc::%@", [self class]);
	[fullName release];
	[userId release];
	[groupId release];
	[roleId release];
	[userName release];
	[projects release];
	[token release];
	[super dealloc];
}

@end
