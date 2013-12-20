//
//  cookieNavUIViewController.h
//  ShareVUE
//
//  Created by Darren Mason on 2/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CookieNav : NSObject {
    id delegate;
	UIButton *button;
	NSString *cookieLabel;
    UIViewController *main;
	UIViewController *detail;
	UIViewController *master;
	
	BOOL masterBeforeDetail;
	BOOL vertical;
	BOOL masterInPortrait;
	BOOL masterInLandscape;
}

@property (nonatomic,retain) NSString *cookieLabel;
@property (nonatomic,retain) UIViewController *master;
@property (nonatomic,retain) UIViewController *detail;
@property (nonatomic, retain) UIViewController *main;
@property (nonatomic, retain) UIButton *button;
@property (nonatomic, assign) BOOL masterBeforeDetail;
@property (nonatomic, retain) id delegate;

@end
