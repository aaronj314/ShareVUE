//
//  ShareVUEAppDelegate_iPad.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ShareVUEAppDelegate_iPad.h"
#import "RootViewController.h"
#import "SignInViewController_iPad.h"
#import "ProjectsGridViewController.h"
#import "ContentDetailViewController.h"
#import "MGSplitViewController.h"
#import "CookieNavStack.h"

#import <AVFoundation/AVFoundation.h>

@implementation ShareVUEAppDelegate_iPad
@synthesize rootViewController;
@synthesize splitViewController;
@synthesize projectsGridViewController;
@synthesize contentDetailViewController;

- (void)dealloc {
	[rootViewController release];
    [splitViewController release];
	[projectsGridViewController release];
    [contentDetailViewController release];
	[super dealloc];
}

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
    // init location service
    //[super initLocationService];
	
	// root view controller
	rootViewController = [[RootViewController alloc] initWithNibName:@"RootViewController" bundle:nil];
	[self.window addSubview:rootViewController.view];
    
    // init sign in controller
    signInViewController = [[SignInViewController_iPad alloc] initWithNibName:@"SignInViewController_iPad" bundle:nil];
	
    // build split view
	splitViewController = [[MGSplitViewController alloc] init];
	[splitViewController setShowsMasterInPortrait:YES];
	
	contentDetailViewController = [[ContentDetailViewController alloc] init];
	//dailiesProjects.contentViewController = detail;
	
	splitViewController.delegate = contentDetailViewController;
	//splitViewController.viewControllers = [NSArray arrayWithObjects:contentDetailViewController, navigationController, nil];
    
    // project grid view
    projectsGridViewController = [[ProjectsGridViewController alloc] initWithNibName:@"ProjectsGridViewController" bundle:nil];
	
	rootViewController.mainViewController = projectsGridViewController;
	[rootViewController presentModalViewController:signInViewController animated:NO];
	
    // Override point for customization after application launch.
    [self.window makeKeyAndVisible];
    
    [[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback error:NULL];
    return YES;
}

@end
