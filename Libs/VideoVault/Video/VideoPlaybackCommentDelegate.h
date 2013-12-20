//
//  VideoPlaybackCommentDelegate.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "VideoPlaybackDelegate.h"

@class PlayerCommentSliderView;

@interface VideoPlaybackCommentDelegate : VideoPlaybackDelegate {
	UIView *commentBox;
	PlayerCommentSliderView *commentSlider;
}
@property (nonatomic, retain) IBOutlet UIView *commentBox;
@property (nonatomic, retain) IBOutlet PlayerCommentSliderView *commentSlider;
@end
