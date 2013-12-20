//
//  ShareVUEAppDelegate_iPad.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ShareVUEAppDelegate.h"


#define APP_IPAD_DELEGATE() \
((ShareVUEAppDelegate_iPad *)[UIApplication sharedApplication].delegate)

#define UIColorFromRGB(rgbValue) [UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0xFF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

@class ProjectsGridViewController;
@class ContentDetailViewController;
@class MGSplitViewController;
@class RootViewController;
@class CookieNavStack;

@interface ShareVUEAppDelegate_iPad : ShareVUEAppDelegate {
	RootViewController *rootViewController;
    MGSplitViewController *splitViewController;
    ProjectsGridViewController *projectsGridViewController;
    ContentDetailViewController *contentDetailViewController;
	CookieNavStack *cookieNavStack;
}
@property (nonatomic, readonly) RootViewController *rootViewController;
@property (nonatomic, retain) MGSplitViewController *splitViewController;
@property (nonatomic, retain) ProjectsGridViewController *projectsGridViewController;
@property (nonatomic, retain) ContentDetailViewController *contentDetailViewController;

@end
