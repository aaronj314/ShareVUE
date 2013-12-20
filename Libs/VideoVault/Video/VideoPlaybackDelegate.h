//
//  VideoPlaybackDelegate.h
//  i360Client
//
//  Created by Aaron Jones on 10/5/10.
//  Copyright 2010 Sorenson Media. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AVFoundation/AVFoundation.h>

@class VideoPlaybackView;
@class AVPlayer;

@interface VideoPlaybackDelegate : NSObject {
	IBOutlet VideoPlaybackView *mPlaybackView;
	
	IBOutlet UISlider *mScrubber;
	IBOutlet UIView *mPlayBar;
	IBOutlet UIView *mPauseBar;
	
	NSURL *mURL;
	NSArray *urls;
	AVPlayer *mPlayer;
	
	float mRestoreAfterScrubbingRate;
	id mTimeObserver;
	id mWatermarkObserver;
	IBOutlet UIImageView *thumbnailView;
	
	//Time lables
	IBOutlet UILabel *currentTime;
	IBOutlet UILabel *remainingTime;
	
	UIImageView *watermark;
    NSTimer *theTimer;
    
    // only temp for a hack with AVAsset
    //@public
    //double durationHack;
}

@property (nonatomic, retain) NSURL *URL;
@property (nonatomic, retain) NSArray *URLS;
@property (nonatomic, retain) id mTimeObserver;
@property (nonatomic, retain) AVPlayer *mPlayer;
@property (nonatomic, retain) VideoPlaybackView *mPlaybackView;
@property (nonatomic, retain) IBOutlet UISlider *mScrubber;
@property (nonatomic, retain) UIView *mPlayBar;
@property (nonatomic, retain) UIView *mPauseBar;
@property (nonatomic, retain) UIImageView *thumbnailView;
@property (nonatomic, retain) UILabel *currentTime;
@property (nonatomic, retain) UILabel *remainingTime;
@property (nonatomic, retain) IBOutlet UIImageView *watermark;

-(void)play:(id)sender;
-(void)pause:(id)sender;
-(BOOL)isPlaying;

-(void)beginScrubbing:(id)sender;
-(void)scrub:(id)sender;
-(void)endScrubbing:(id)sender;
-(BOOL)isScrubbing;
-(void)setScrubberToTime:(double)time;
-(double)getCurrentTime;
-(void)stop:(id)sender;
-(void)showLoadingAlertView;

-(void)syncButtons;
-(void)syncScrubber;
@end
