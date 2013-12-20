//
//  ShareVUEAppDelegate.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#import <UIKit/UIKit.h>
#import <CoreLocation/CoreLocation.h>

#define APP_DELEGATE() \
((ShareVUEAppDelegate *)[UIApplication sharedApplication].delegate)


@class SignInViewController;
@class Account;
@class User;

@interface ShareVUEAppDelegate : NSObject <UIApplicationDelegate, CLLocationManagerDelegate> {
    UINavigationController *navigationController;
    SignInViewController *signInViewController;
    CLLocationManager *locMgr;
	NSMutableArray *cookieTrail;
    
    // top level objs
    Account *account;
	User *user;
	NSMutableArray *videos;
    
    @public
	BOOL locked;
}

-(NSMutableArray *)cookieTrail;

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain, readonly) NSManagedObjectContext *managedObjectContext;
@property (nonatomic, retain, readonly) NSManagedObjectModel *managedObjectModel;
@property (nonatomic, retain, readonly) NSPersistentStoreCoordinator *persistentStoreCoordinator;
@property (nonatomic, readonly) UINavigationController *navigationController;
@property (nonatomic, readonly) SignInViewController *signInViewController;
@property (nonatomic, retain) CLLocationManager *locMgr;
@property (nonatomic, retain) Account *account;
@property (nonatomic, retain) User *user;
@property (nonatomic, retain) NSMutableArray *videos;

- (void)saveContext;
- (NSURL *)applicationDocumentsDirectory;
-(void)initLocationService;
@end
