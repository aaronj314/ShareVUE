//
//  ProjectPlaylistViewController_iPad.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ProjectPlaylistViewController.h"
#import "MGSplitViewController.h"

@class ContentDetailViewController;
@class VideoPlayFullViewController;

@interface ProjectPlaylistViewController_iPad : ProjectPlaylistViewController <UIPopoverControllerDelegate, MGSplitViewControllerDelegate> {
    ContentDetailViewController *contentDetailViewController;
	UIPopoverController *popoverController;
	VideoPlayFullViewController *videoFullViewController;
}
@property(nonatomic, retain) ContentDetailViewController *contentDetailViewController;
@property (nonatomic, retain) UIPopoverController *popoverController;
@end
