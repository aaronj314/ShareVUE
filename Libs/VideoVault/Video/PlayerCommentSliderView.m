//
//  PlayerCommentSliderView.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlayerCommentSliderView.h"
#import "PDColoredProgressView.h"

#define kSliderHeight			23.0
#define kUIProgressBarHeight	 9.0

@implementation PlayerCommentSliderView
@synthesize slider, progressView;

-(id)initWithCoder:(NSCoder *)aDecoder {
	self = [super initWithCoder:aDecoder];
	if (self) {
		slider = [[UISlider alloc] initWithFrame:CGRectMake(0, 0, self.frame.size.width, kSliderHeight)];
		slider.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
		UIImage *stetchLeftTrack = [[UIImage imageNamed:@"sliderLeftGreen.png"] stretchableImageWithLeftCapWidth:10.0 topCapHeight:0.0];
		UIImage *stetchRightTrack = [[UIImage imageNamed:@"sliderRightClear.png"] stretchableImageWithLeftCapWidth:10.0 topCapHeight:0.0];
		[slider setThumbImage: [UIImage imageNamed:@"sliderBall.png"] forState:UIControlStateNormal];
		[slider setMinimumTrackImage:stetchLeftTrack forState:UIControlStateNormal];
		[slider setMaximumTrackImage:stetchRightTrack forState:UIControlStateNormal];
		slider.minimumValue = 0.0;
		slider.maximumValue = 1.0;
		slider.continuous = YES;
		slider.value = 0.0;
		
		progressView = [[PDColoredProgressView alloc] initWithFrame:CGRectMake(2, 7, self.frame.size.width-2, kUIProgressBarHeight)];
		[progressView setTintColor: [[UIColor greenColor] colorWithAlphaComponent:0.3]];
		progressView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
		progressView.progress = 0.0f;
		
		/*
		UIButton *marker = [UIButton buttonWithType:UIButtonTypeCustom];
		marker.frame = CGRectMake(0, 0, 15, 25);
		[marker setBackgroundImage:[UIImage imageNamed:@"marker.png"] forState:UIControlStateNormal];
		[marker addTarget:self action:@selector(showComment:) forControlEvents:UIControlEventTouchUpInside];
		marker.center = CGPointMake(20, 15);
		*/
		
		//[self addSubview:marker];
		[self addSubview:progressView];
		[self addSubview:slider];
	}
	return self;
}

- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
		CGRect sliderFrame = CGRectMake(0, 0, frame.size.width, kSliderHeight);
		slider = [[UISlider alloc] initWithFrame:sliderFrame];
		
		UIImage *stetchLeftTrack = [[UIImage imageNamed:@"sliderLeftOrange.png"] stretchableImageWithLeftCapWidth:10.0 topCapHeight:0.0];
		UIImage *stetchRightTrack = [[UIImage imageNamed:@"sliderRightGray.png"] stretchableImageWithLeftCapWidth:10.0 topCapHeight:0.0];
		[slider setThumbImage: [UIImage imageNamed:@"sliderBall.png"] forState:UIControlStateNormal];
		[slider setMinimumTrackImage:stetchLeftTrack forState:UIControlStateNormal];
		[slider setMaximumTrackImage:stetchRightTrack forState:UIControlStateNormal];
		slider.minimumValue = 0.0;
		slider.maximumValue = 1.0;
		slider.continuous = YES;
		slider.value = 0.0;
		progressView = [[PDColoredProgressView alloc] initWithFrame:CGRectMake(2, 7, self.frame.size.width-2, kUIProgressBarHeight)];
		[progressView setTintColor: [UIColor cyanColor]];
		progressView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleTopMargin;
		progressView.progress = 0.0f;
		[self addSubview:progressView];
		[self addSubview:slider];
    }
    return self;
}

-(void)addTarget:(id)target action:(SEL)action forControlEvents:(UIControlEvents)controlEvents {
	
	[slider addTarget:target action:action forControlEvents:controlEvents];
}

-(void)setProgressValue:(CGFloat)value {
	[progressView setProgress:value animated:YES];
}

-(void)showComment:(id)sender {
	NSLog(@"Marker touched");
}


- (void)dealloc {
	//NSLog(@"dealloc::%@", [self class]);
	[slider release];
	[progressView release];
    [super dealloc];
}



@end
