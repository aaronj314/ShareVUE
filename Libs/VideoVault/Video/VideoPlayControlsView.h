//
//  VideoPlayControlsView.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/31/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PlayerCommentSliderView;
@class VideoPlaybackCommentDelegate;

@interface VideoPlayControlsView : UIView {
	IBOutlet UIToolbar *topBar, *playBar, *pauseBar, *doneBar;
	IBOutlet UILabel *currentTime;
	IBOutlet UILabel *remainingTime;
	IBOutlet PlayerCommentSliderView *slider;
	IBOutlet UIView *buttonBar;
	VideoPlaybackCommentDelegate *playbackDelegate;
}
@property (nonatomic, retain) PlayerCommentSliderView *slider;
@property (nonatomic, retain) UIView *buttonBar;
@property (nonatomic, retain) UIToolbar *playBar, *pauseBar;
@property (nonatomic, retain) UILabel *currentTime;
@property (nonatomic, retain) UILabel *remainingTime;
@property (nonatomic, retain) VideoPlaybackCommentDelegate *playbackDelegate;
-(void)hideControls;
@end
 