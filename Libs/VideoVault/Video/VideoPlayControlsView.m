//
//  VideoPlayControlsView.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/31/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "VideoPlayControlsView.h"
#import "PlayerCommentSliderView.h"
#import "VideoPlaybackCommentDelegate.h"


@implementation VideoPlayControlsView
@synthesize slider, buttonBar, pauseBar, playBar, currentTime, remainingTime, playbackDelegate;

- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
}

-(void)hideControls {
	topBar.hidden = !topBar.hidden;
    playBar.hidden = !playBar.hidden;
    pauseBar.hidden = !pauseBar.hidden;
    doneBar.hidden = !doneBar.hidden;
	currentTime.hidden = !currentTime.hidden;
	remainingTime.hidden = !remainingTime.hidden;
	slider.hidden = !slider.hidden;
	buttonBar.hidden = !buttonBar.hidden;
}

-(void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
	//NSLog(@"touch began");
}

-(void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
	//NSLog(@"touch Ended");
	//if (slider.hidden) {
	//	[playbackDelegate pause:self];
	//}
	//[self hideControls];
}


/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
}
*/

- (void)dealloc {
    [playBar release];
    [pauseBar release];
    [doneBar release];
	[playbackDelegate release];
	[topBar release];
	[buttonBar release];
	[currentTime release];
	[remainingTime release];
	[slider release];
    [super dealloc];
}


@end
