    //
//  RootViewController.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "RootViewController.h"
#import "MGSplitViewController.h"
#import "ShareVUEAppDelegate_iPad.h"
#import <QuartzCore/QuartzCore.h>

@implementation RootViewController
@synthesize mainViewController;
@synthesize containerView;
@synthesize backCookieTrailView;
@synthesize mainViewRef;
@synthesize headerBar;
@synthesize currentLoggedIn;
@synthesize cookieNavView;
@synthesize statusView;
@synthesize statusProgressView;
@synthesize statusLabel;



- (void)dealloc {
	[statusLabel release];
	[statusProgressView release];
	[statusView release];
	[cookieNavView release];
	[currentLoggedIn release];
	[backCookieTrailView release];
	[mainViewRef release];
	[containerView release];
	[headerBar release];
	[mainViewController release];
    [super dealloc];
}
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {	
    [super viewDidLoad];
	UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:statusView.frame cornerRadius: 18.0];
    //statusView.layer.shadowPath = path.CGPath;
	statusView.layer.cornerRadius = 10.0f;
	statusView.layer.shadowRadius = 10.0;
    statusView.layer.shadowOpacity = 0.4;
    statusView.layer.shadowOffset = CGSizeMake( 2.0, 2.0 );
}



- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    //return YES;
    return ((interfaceOrientation == UIInterfaceOrientationLandscapeLeft) || (interfaceOrientation == UIInterfaceOrientationLandscapeRight));
}


- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

-(IBAction)signOut:(id)sender {
	ShareVUEAppDelegate_iPad *appDelegate  = APP_IPAD_DELEGATE();
	[appDelegate.signInViewController signOut:sender];
}

-(void)setMainViewController:(UIViewController *)controller {
	if (mainViewController != controller) {
	
		[mainViewController.view removeFromSuperview];
		id tmp = mainViewController;
		mainViewController = [controller retain];
		/*
		NSLog(@"=======Will setMainViewController container.view==%@", NSStringFromCGRect(containerView.frame));
		NSLog(@"=======Will setMainViewController self.view==%@", NSStringFromCGRect(self.view.frame));
		NSLog(@"=======Will setMainViewController mainViewController.view==%@", NSStringFromCGRect(mainViewController.view.frame));
		*/
		if ([mainViewController isKindOfClass:[MGSplitViewController class]]) {
			CGRect old = mainViewController.view.frame;
			mainViewController.view.clipsToBounds = YES;
			mainViewController.view.autoresizesSubviews = NO;
			mainViewController.view.frame = CGRectMake(0, 0, old.size.width, old.size.height);
		}
		
		if (UIInterfaceOrientationIsLandscape(self.interfaceOrientation)) {
			//mainViewController.view.frame = CGRectMake(0,0,1024,768-45);
			[self willRotateToInterfaceOrientation:self.interfaceOrientation duration:0];
			
		}
		
		
		//self.mainViewRef = mainViewController.view;
		/*
		if (self.interfaceOrientation == UIInterfaceOrientationLandscapeLeft || self.interfaceOrientation == UIInterfaceOrientationLandscapeRight) {
			mainViewController.view.frame = CGRectMake(0, 0, 1024, 768);
		} else {
			mainViewController.view.frame = CGRectMake(0, 0, 768, 1024);
		}*/
		//mainViewController.view.autoresizingMask = UIViewAutoresizingFlexibleTopMargin | UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
		[tmp release];
		[containerView addSubview:mainViewController.view];
		//[self willRotateToInterfaceOrientation:self.interfaceOrientation duration:0.0f];
	}
}


- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
	//[super willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
	//NSLog(@"=======Will rotate container.view==%@", NSStringFromCGRect(containerView.frame));
	//NSLog(@"=======Will rotate self.view==%@", NSStringFromCGRect(self.view.frame));
	//NSLog(@"=======Will rotate mainViewController.view==%@", NSStringFromCGRect(mainViewController.view.frame));
	if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation)) {
		//self.view.frame = CGRectMake(0, 0, 1024, 768);
		headerBar.frame = CGRectMake(0, 0, 1024, 45);
		containerView.frame = CGRectMake(0, 45, 1024, 768-45);
		mainViewController.view.frame = CGRectMake(0,0,1024,768-45);
		//NSLog(@"L=======Will rotate RootViewController==%@", NSStringFromCGRect(mainViewController.view.frame));
		///mainViewController.view.frame = CGRectMake(0, 0, 1024, 608);
		//NSLog(@"------Will rotate RootViewController==%@", NSStringFromCGRect(mainViewController.view.frame));
	} else {
		//if ([mainViewController isKindOfClass:[MGSplitViewController class]]) {
		//	[mainViewController setMasterBeforeDetail:NO];
		//}
		//self.view.frame = CGRectMake(0, 0, 768, 1024);
		headerBar.frame = CGRectMake(0, 0, 768, 45);
		containerView.frame = CGRectMake(0, 45, 768, 1024-45);
		//self.view.frame = CGRectMake(0, 0, 768, 1024);
		//NSLog(@"P=======Will rotate RootViewController==%@", NSStringFromCGRect(mainViewController.view.frame));
		mainViewController.view.frame = CGRectMake(0, 0, 768, 1024-45);
		
		///NSLog(@"++++++Will rotate RootViewController==%@", NSStringFromCGRect(mainViewController.view.frame));
	}
	[self.mainViewController willRotateToInterfaceOrientation:toInterfaceOrientation duration:duration];
}


- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation
{
	[self.mainViewController didRotateFromInterfaceOrientation:fromInterfaceOrientation];
}


- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation 
										 duration:(NSTimeInterval)duration
{
	[self.mainViewController willAnimateRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
	
}


- (void)willAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
	[self.mainViewController willAnimateFirstHalfOfRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
}


- (void)didAnimateFirstHalfOfRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation
{
	[self.mainViewController didAnimateFirstHalfOfRotationToInterfaceOrientation:toInterfaceOrientation];
}


- (void)willAnimateSecondHalfOfRotationFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation duration:(NSTimeInterval)duration
{
	[self.mainViewController willAnimateSecondHalfOfRotationFromInterfaceOrientation:fromInterfaceOrientation duration:duration];
}




@end
