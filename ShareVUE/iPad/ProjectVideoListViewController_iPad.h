//
//  ProjectVideoListViewController_iPad.h
//  ShareVUE
//
//  Created by Aaron Jones on 3/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProjectVideoListViewController.h"
#import "MGSplitViewController.h"

@class ContentDetailViewController;
@class VideoPlayViewController;

@interface ProjectVideoListViewController_iPad : ProjectVideoListViewController<UIPopoverControllerDelegate, MGSplitViewControllerDelegate>  {
    ContentDetailViewController *contentDetailViewController;
	UIPopoverController *popoverController;
	VideoPlayViewController *videoPlayViewController;
	
	@public
	int selectedIdx;
}
@property(nonatomic, retain) ContentDetailViewController *contentDetailViewController;
@property (nonatomic, retain) UIPopoverController *popoverController;
@property (nonatomic, retain) VideoPlayViewController *videoPlayViewController;
@end
