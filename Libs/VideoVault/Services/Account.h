//
//  Account.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AccountConfig.h"

@class Account;
@class User;
@class Project;
@class SourceVideo;
@class Comment;
@class Playlist;
@class Asset;

typedef void (^BasicBlock)(void);

typedef void (^SignInResultsBlock)(Account *account, NSError *error);
typedef void (^ProjectsResultsBlock)(NSMutableArray *projects, NSError *error);
typedef void (^VideosResultsBlock)(NSMutableArray *videos, NSError *error);
typedef void (^CommentsResultsBlock)(NSMutableArray *comments, NSError *error);
typedef void (^PlaylistsResultsBlock)(NSMutableArray *playlists, NSError *error);
typedef void (^AssetsResultsBlock)(NSMutableArray *assets, NSError *error);

typedef void (^GetResultsBlock)(id object, NSError *error);
typedef void (^CreateResultsBlock)(id object, NSError *error);
typedef void (^UpdateResultsBlock)(id object, NSError *error);
typedef void (^DeleteResultsBlock)(id object, NSError *error);

#ifdef DEBUG
//static NSString * const TEST_USER_NAME = @"12datesofchristmas@admin.com";
//static NSString * const TEST_PASSWD = @"Admin!@#$";
static NSString * const TEST_USER_NAME = @"tcnadmin@sorensonmedia.com";
static NSString * const TEST_PASSWD = @"S0r3ns0nM3d1@";
//static NSString * const TEST_USER_NAME = @"smedia@sorensonmedia.com";
//static NSString * const TEST_PASSWD = @"test1234";
//static NSString * const TEST_USER_NAME = @"admin";
//static NSString * const TEST_PASSWD = @"S0r3ns0n";
//static NSString * const TEST_USER_NAME = @"relativity";
//static NSString * const TEST_PASSWD = @"demo";
//static NSString * const TEST_USER_NAME = @"demo@sorensonmedia.com";
//static NSString * const TEST_PASSWD = @"demo";

//
//static NSString * const TEST_USER_NAME = @"admin@americanreunion.com";
//static NSString * const TEST_PASSWD = @"4dm1n";
#endif

//static NSString * const _BACKEND_HOST = @"http://dev-videovault.sorensonmedia.com/vapi/";
//static NSString * const _BACKEND_HOST = @"http://stage-videovault.sorensonmedia.com/vapi/";
//static NSString * const _BACKEND_HOST = @"https://stage.sorensondns.com/vapi/";
static NSString * const _BACKEND_HOST = @"https://sharevue.technicolor.com/vapi/";


static NSString * const X_AUTH_TOKEN = @"X-Videovault-Auth-Token";
static NSString * const X_DEVICE_MAC = @"x-videovault-device-address";

@interface Account : NSObject {
	User *user;
}
@property (nonatomic, retain) User *user;

+(void)signInWithUsername:(NSString *)username password:(NSString *)password resultsBlock:(SignInResultsBlock)resultsBlock;

@end
