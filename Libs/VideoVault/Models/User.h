//
//  User.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Project;

@interface User : NSObject {
	NSString *userId;
	NSString *fullName;
	NSString *userName;
	NSString *groupId;
	NSString *roleId;
	NSString *token;
	NSMutableArray *projects;
}
@property (nonatomic, retain) NSString *userId, *userName, *groupId, *roleId, *fullName;
@property (nonatomic, retain) NSString *token;
@property (nonatomic, retain) NSMutableArray *projects;



+(User *)userForDemo;
@end
