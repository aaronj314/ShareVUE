//
//  RootViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@class CookieNavView;

@interface RootViewController : UIViewController {
	UIViewController *mainViewController;
	UIView *containerView;
	UIView *mainViewRef;
	UIView *headerBar;
	UIView *backCookieTrailView;
	UILabel *currentLoggedIn;
	CookieNavView *cookieNavView;
	
	//status view
	UIView *statusView;
	UIProgressView *statusProgressView;
	UILabel *statusLabel;
}

@property (nonatomic,retain) IBOutlet UILabel *currentLoggedIn;
@property (nonatomic,retain) IBOutlet UIView *backCookieTrailView;
@property (nonatomic, retain) UIViewController *mainViewController;
@property (nonatomic, retain) IBOutlet UIView *containerView;
@property (nonatomic, retain) IBOutlet UIView *mainViewRef;
@property (nonatomic, retain) IBOutlet UIView *headerBar;
@property (nonatomic, retain) IBOutlet CookieNavView *cookieNavView;
@property (nonatomic, retain) IBOutlet UIView *statusView;
@property (nonatomic, retain) IBOutlet UIProgressView *statusProgressView;
@property (nonatomic, retain) IBOutlet UILabel *statusLabel;
-(IBAction)signOut:(id)sender;

@end
