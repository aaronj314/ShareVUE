//
//  VideoPlaybackListViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VideoPlaybackListViewController.h"
#import "MGSplitViewController.h"

@class ContentDetailViewController;
@class VideoPlayViewController;

@interface VideoPlaybackListViewController_iPad : VideoPlaybackListViewController <UIPopoverControllerDelegate, MGSplitViewControllerDelegate>  {
    ContentDetailViewController *contentDetailViewController;
	UIPopoverController *popoverController;
	VideoPlayViewController *videoPlayViewController;
}
@property(nonatomic, retain) ContentDetailViewController *contentDetailViewController;
@property (nonatomic, retain) UIPopoverController *popoverController;
@property (nonatomic, retain) VideoPlayViewController *videoPlayViewController;
@end
