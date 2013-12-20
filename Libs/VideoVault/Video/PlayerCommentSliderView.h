//
//  PlayerCommentSliderView.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PDColoredProgressView;

@interface PlayerCommentSliderView : UIControl {
	UISlider *slider;
	PDColoredProgressView *progressView;
	
}
@property(nonatomic, retain) UISlider *slider;
@property (nonatomic, retain) PDColoredProgressView *progressView;

-(void)setProgressValue:(CGFloat)value;
@end
