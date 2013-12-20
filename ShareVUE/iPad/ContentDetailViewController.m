//
//  ProjectDetailViewController_iPad.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/29/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ContentDetailViewController.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "MGSplitCornersView.h"
#import "RootViewController.h"



@implementation ContentDetailViewController
@synthesize toolbar, contentController, popoverController;

-(id)init {
	if ((self = [super init])) {
		//toolbar = [[UIToolbar alloc] initWithFrame:CGRectMake(0, 0, 10, 44)];
		//toolbar.autoresizingMask = UIViewAutoresizingFlexibleWidth;
		//toolbar.barStyle = UIBarStyleBlack;
		//toolbar.items = [NSArray array];
	}
	return self;
}

- (void) dealloc {
	//NSLog(@"dealloc::%@", [self class]);
	[contentController release];
	[popoverController release];
	[toolbar release];
	[super dealloc];
}


-(void)loadView {
	self.view = [[[UIView alloc] initWithFrame:CGRectZero] autorelease];
	self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight  | UIViewAutoresizingFlexibleLeftMargin | UIViewAutoresizingFlexibleRightMargin;
	//self.view.autoresizingMask = UIViewAutoresizingFlexibleTopMargin | UIViewAutoresizingFlexibleLeftMargin;
	self.view.alpha = 1.0;
	self.view.clipsToBounds = YES;
	//self.view.backgroundColor = [UIColor ];
	self.view.autoresizesSubviews = YES;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return YES;
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
}

-(void)addTitle:(NSString *)title {
    //UIBarButtonItem *barTitle = [[UIBarButtonItem alloc] initWithTitle:title style:UIBarButtonItemStylePlain target:nil action:nil];
    //NSMutableArray *items = [[toolbar items] mutableCopy];
	//[items removeAllObjects];
    //[items insertObject:barTitle atIndex:0];
    //[toolbar setItems:items animated:YES];
    //[barTitle release];
    //[items release];
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	//NSLog(@"Rotate 1=%@",NSStringFromCGRect(self.view.frame));
	CGRect f;
	if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation)) {
		//if (!appDelegate.splitViewController.isVertical) {
		//	[appDelegate.splitViewController toggleSplitOrientation:self];
		//}
		//f = CGRectMake(0, 0, 600, 900);
		
		appDelegate.splitViewController.vertical = YES;
	} else {
		//[appDelegate.splitViewController setShowsMasterInPortrait:NO];
		//if (appDelegate.splitViewController.isVertical) {
		//	[appDelegate.splitViewController toggleSplitOrientation:self];
		//}
		//f = CGRectMake(0, 33, 703, 748);
		
		appDelegate.splitViewController.vertical = NO;
	}
	//NSLog(@"Rotate 11=%@",NSStringFromCGRect(contentController.view.frame));

	//contentController.view.frame = f;
	[contentController willAnimateRotationToInterfaceOrientation:toInterfaceOrientation duration:duration];
}

-(void)toggleLogo:(BOOL)b {
	
	[self.view viewWithTag:7].hidden = b;
}

/*
 When setting the detail item, update the view and dismiss the popover controller if it's showing.
 */
-(void)setDetailItem:(id)newDetailItem {
    if (contentController != newDetailItem) {
        
		[contentController.view removeFromSuperview];
        self.contentController = newDetailItem;
        // Update the view.
        [self configureView];
        //contentController.view.alpha = 0;
        //[UIView beginAnimations:@"FadeInContentView" context:nil];
        //contentController.view.alpha = 1.0;
        //[UIView commitAnimations];
    }
	
    if (popoverController != nil) {
        [popoverController dismissPopoverAnimated:YES];
    }        
}

-(void)configureView {
    // Update the user interface for the detail item.
	CGRect frame = self.view.frame;
	//NSLog(@"ContentDetailView.frame=%@", NSStringFromCGRect(frame));
	contentController.view.frame = CGRectMake(0, 0, frame.size.width, frame.size.height - 44);
	//contentController.view.frame = CGRectMake(0, 0, frame.size.width, frame.size.height);
	contentController.view.autoresizingMask = UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleWidth;
	contentController.view.tag = 69;
	[self.view addSubview:contentController.view];
}

#pragma mark - 
#pragma mark Split view support

- (void)splitViewController: (MGSplitViewController*)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem*)barButtonItem forPopoverController: (UIPopoverController*)pc {
    
    //barButtonItem.title = @"Playlists";
    //NSMutableArray *items = [[toolbar items] mutableCopy];
    //[items insertObject:barButtonItem atIndex:0];
    //[toolbar setItems:items animated:YES];
    //[items release];
   // self.popoverController = pc;
}

// Called when the view is shown again in the split view, invalidating the button and popover controller.
- (void)splitViewController: (MGSplitViewController*)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem {
    
    //NSMutableArray *items = [[toolbar items] mutableCopy];
    //[items removeObjectAtIndex:0];
    //[toolbar setItems:items animated:YES];
    //[items release];
    //self.popoverController = nil;
}

- (void)splitViewController:(MGSplitViewController*)svc willChangeSplitOrientationToVertical:(BOOL)isVertical
{
	//NSLog(@"Will hange to vertical%@", NSStringFromSelector(_cmd));
}

@end
