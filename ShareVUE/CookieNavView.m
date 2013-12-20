//
//  CookieNavView.m
//  ShareVUE
//
//  Created by Aaron Jones on 3/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CookieNavView.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "MGSplitViewController.h"
#import "RootViewController.h"
#import "ContentDetailViewController.h"

@implementation CookieNavView
@synthesize navStack;

- (void)dealloc {
	[navStack release];
    [super dealloc];
}

-(id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        navStack = [[CookieNavStack alloc] init];
    }
    return self;
}

- (id)initWithCoder:(NSCoder *)decoder {
	self = [super initWithCoder:decoder];
    if (self) {
        navStack = [[CookieNavStack alloc] init];
    }
    return self;
}
/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
}
*/

-(void)flushView {
	[navStack clear];
	for (UIView *v in [self subviews]) {
		[v removeFromSuperview];
	}
}

-(void)pushWithTitle:(NSString *)title cookie:(CookieNav *)cookie {
	UIButton *backButton = [UIButton buttonWithType:UIButtonTypeCustom];
	
	// position in the parent view and set the size of the button
	
	if ([navStack count] == 0) {
        backButton.tag = 0;
		backButton.frame = CGRectMake(0, 0, 120.0f, 40.0f);
	} else {
        backButton.tag = [navStack count];
		backButton.frame = CGRectMake(105, 0, 200.0f, 40.0f);
	}

	
	
	backButton.titleLabel.font =[UIFont fontWithName:@"Helvetica" size:14.0];
	backButton.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
	[backButton setTitleColor:UIColorFromRGB(0xff0e6fb9) forState:UIControlStateNormal];
	[backButton setTitleColor:[UIColor redColor] forState:UIControlStateSelected];
	[backButton setTitle:title forState:UIControlStateNormal];
	
	[backButton addTarget:self action:@selector(linkPressed:) forControlEvents:UIControlEventTouchUpInside];
	[navStack push:cookie];
	[self addSubview:backButton];
}
-(void)pop {
	CookieNav *cookie = [navStack pop];
	[[self viewWithTag:cookie.button.tag] removeFromSuperview]; 
}

-(void)popToRoot {
    [navStack popToRoot];
}

-(void)linkPressed:(id)sender {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE(); 
	NSInteger idx = ((UIView *)sender).tag;
	[((UIView *)sender) removeFromSuperview];
    if (idx == 0) {
        CookieNav *cookie = [navStack popToRoot];
        [cookie.delegate navPop];
		for (UIView *v in [self subviews]) {
			[v removeFromSuperview];
		}
        appDelegate.rootViewController.mainViewController = cookie.main;
    } else {
        CookieNav *cookie = [navStack pop];
        [cookie.delegate navPop];
        MGSplitViewController *splitVC = appDelegate.splitViewController;
        splitVC.masterViewController = cookie.master;
        //splitVC.masterBeforeDetail = cookie.masterBeforeDetail;
        
        ContentDetailViewController *detail = (ContentDetailViewController *)splitVC.detailViewController;
        [detail setDetailItem:cookie.detail];
        [appDelegate.splitViewController toggleMasterBeforeDetail:self];
        
    }
	
}
@end
