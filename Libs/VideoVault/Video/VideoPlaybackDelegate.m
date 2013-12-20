//
//  VideoPlaybackDelegate.m
//  i360Client
//
//  Created by Aaron Jones on 10/5/10.
//  Copyright 2010 Sorenson Media. All rights reserved.
//
#import <AVFoundation/AVFoundation.h>
#import "VideoPlaybackDelegate.h"
#import "VideoPlaybackView.h"
#import "VideoLoadingStatusView.h"

static int retryCount = 0;
static int retryMaxCount = 1;

@interface VideoPlaybackDelegate()
- (void)syncButtons;
- (void)syncScrubber;
@end

static NSString* const VideoPlaybackViewDelegateRateObservationContext = @"VideoPlaybackViewDelegateRateObservationContext";
static NSString* const VideoPlaybackViewDelegateDurationObservationContext = @"VideoPlaybackViewDelegateDurationObservationContext";
static NSString* const VideoPlaybackViewDelegateStatusContext = @"VideoPlaybackViewDelegateStatusContext";
static NSString* const VideoPlaybackViewDelegateLoadedTimeRangesContext = @"VideoPlaybackViewDelegateLoadedTimeRangesContext";

@implementation VideoPlaybackDelegate
@synthesize mPlaybackView, mPlayer, mPlayBar, mScrubber, mTimeObserver, mPauseBar, thumbnailView;
@synthesize currentTime, remainingTime, watermark;

-(void)stop:(id)sender {
	if (mTimeObserver) {
		[mPlayer removeTimeObserver:mTimeObserver];
		//dispatch_sync(dispatch_get_main_queue(), ^{});
		[mTimeObserver release];
		mTimeObserver = nil;
	}
	
	//if (mWatermarkObserver) {
	//	[mPlayer removeTimeObserver:mWatermarkObserver];
	//	mTimeObserver = nil;
	//	[mWatermarkObserver release];
	//}
	[mPlayer pause];
}

/*
-(void)setMPlaybackView:(VideoPlaybackView *)view {
    if (mPlaybackView != view) {
        [mPlaybackView release];
        mPlaybackView = [view retain];
	
        [mPlaybackView setPlayer:mPlayer];
        [self setup];
    }
}
*/

-(void)dealloc {
	//NSLog(@"dealloc->>%@", [super class]);
	if (mTimeObserver) {
		[mPlayer removeTimeObserver:mTimeObserver];
		[mTimeObserver release];
		mTimeObserver = nil;
	}
	if (mWatermarkObserver) {
		[mPlayer removeTimeObserver:mWatermarkObserver];
		[mWatermarkObserver release];
		mWatermarkObserver = nil;
	}
	
	
	[mPlayer removeObserver:self forKeyPath:@"rate"];
	//[mPlayer removeObserver:self forKeyPath:@"currentItem.asset.duration"];
    [mPlayer removeObserver:self forKeyPath:@"currentItem.duration"];
	[mPlayer removeObserver:self forKeyPath:@"currentItem.status"];
	[mPlayer removeObserver:self forKeyPath:@"currentItem.loadedTimeRanges"];
	[mPlayer pause];
    //NSLog(@"mPlayer release count >>>>>>> %i", [mPlayer retainCount]);
	[mPlayer release];
	//NSLog(@"mPlayer release count >>>>>>> %i", [mPlayer retainCount]);
	[mURL release];
	[urls release];
	[mScrubber release];
	[mPauseBar release];
	[currentTime release];
    [remainingTime release];
	[thumbnailView release];
	[mPlaybackView release];
    if (!theTimer) {
        [theTimer invalidate];
    }
    [theTimer release];
	[watermark release];
	[super dealloc];
}

-(void)initPlayer {
	mPlayer = [[AVPlayer allocWithZone:[self zone]] initWithURL:mURL];
	[mPlayer addObserver:self forKeyPath:@"rate" options:0 context:VideoPlaybackViewDelegateRateObservationContext];
	//[mPlayer addObserver:self forKeyPath:@"currentItem.asset.duration" options:0 context:VideoPlaybackViewDelegateDurationObservationContext];
    [mPlayer addObserver:self forKeyPath:@"currentItem.duration" options:0 context:VideoPlaybackViewDelegateDurationObservationContext];
	[mPlayer addObserver:self forKeyPath:@"currentItem.status" options:0 context:VideoPlaybackViewDelegateStatusContext];
	[mPlayer addObserver:self forKeyPath:@"currentItem.loadedTimeRanges" options:0 context:VideoPlaybackViewDelegateLoadedTimeRangesContext];
}

-(void)initQueuePlayer {
	NSMutableArray *items = [NSMutableArray	arrayWithCapacity:[urls count]];
	for (NSURL *url in urls) {
		AVPlayerItem *item = [[AVPlayerItem alloc] initWithURL:url];
		[items addObject:item];
		[item release];
	}
	
	mPlayer = [[AVQueuePlayer allocWithZone:[self zone]] initWithItems:items];
	[mPlayer addObserver:self forKeyPath:@"rate" options:0 context:VideoPlaybackViewDelegateRateObservationContext];
	//[mPlayer addObserver:self forKeyPath:@"currentItem.asset.duration" options:0 context:VideoPlaybackViewDelegateDurationObservationContext];
    [mPlayer addObserver:self forKeyPath:@"currentItem.duration" options:0 context:VideoPlaybackViewDelegateDurationObservationContext];
	[mPlayer addObserver:self forKeyPath:@"currentItem.status" options:0 context:VideoPlaybackViewDelegateStatusContext];
	[mPlayer addObserver:self forKeyPath:@"currentItem.loadedTimeRanges" options:0 context:VideoPlaybackViewDelegateLoadedTimeRangesContext];
}

-(id)init {
	self = [super init];
	if (self != nil) {
		/*
		mPlayer = [[AVPlayer allocWithZone:[self zone]] init];
		[mPlayer addObserver:self forKeyPath:@"rate" options:0 context:VideoPlaybackViewDelegateRateObservationContext];
		[mPlayer addObserver:self forKeyPath:@"currentItem.asset.duration" options:0 context:VideoPlaybackViewDelegateDurationObservationContext];
		[mPlayer addObserver:self forKeyPath:@"currentItem.status" options:0 context:VideoPlaybackViewDelegateStatusContext];
		[mPlayer addObserver:self forKeyPath:@"currentItem.loadedTimeRanges" options:0 context:VideoPlaybackViewDelegateLoadedTimeRangesContext];
		 */
	}
	return self;
}



-(void)setup {
//	double interval = 0.10;
	double interval = 0.01;
	AVPlayerItem* asset = mPlayer.currentItem;
	
	if (asset) {
		double duration = CMTimeGetSeconds(asset.duration);
		
		if (isfinite(duration))
		{
			CGFloat width = CGRectGetWidth([mScrubber bounds]);
			interval = 0.5 * duration / width;
		}
	}
	
	if (mTimeObserver) {
		@try {
			[mPlayer removeTimeObserver:mTimeObserver];
		}
		@catch (NSException *e) {
			//NSLog(@"ERROR REMOVING TIME OBSERVER=%@", e);
		}
		
		[mTimeObserver release];
	}
	
	//NSLog(@"Interval for player is =%f", interval);
	
	mTimeObserver = [[mPlayer addPeriodicTimeObserverForInterval:CMTimeMakeWithSeconds(interval, NSEC_PER_SEC) queue:dispatch_get_main_queue() usingBlock:
					  ^(CMTime time) {
						 [self syncScrubber];
						 /* 
						  static int dir1 = 1;
						  static int dir2 = 1;
						  static double rate = 0.1;
						  
						  CGRect f1 = mPlaybackView.frame;
						  CGRect f2 = watermark.frame;
						 // NSLog(@"++++++++++++++Frame1=%@, Frame2=%@ UIImage=%@",NSStringFromCGRect(f1), NSStringFromCGRect(f2), watermark);
						  watermark.center = CGPointMake(watermark.center.x +dir1*rate, watermark.center.y +dir2*rate);
						  if (!CGRectContainsRect(f1, f2)) {
							  
							  dir1 *= -1;//(arc4random() % 2 ? 1 : -1);
							  dir2 *= -1;//(arc4random() % 2 ? 1 : -1);
							  watermark.center = CGPointMake(watermark.center.x +10.0*(dir1*rate), watermark.center.y +10.0*(dir2*rate));
						  }*/
					  }] retain];
	//
	[self syncButtons];
    [self syncScrubber];
}

-(NSURL*)URL {
	return mURL;
}

-(NSArray *)URLS {
	return urls;
}

-(void)setPlaybackView:(UIView *)v {
	self.mPlaybackView = (VideoPlaybackView *)v;
	[mPlaybackView setPlayer:mPlayer];
}

/*
 * Call this first and set the URL then call play:
 *
 */
-(void)setURL:(NSURL*)URL {
	if (mURL != URL) {
        //NSLog(@"SETTING URL FOR Video Player Delegate=%@", URL);
        //NSValue *wrappedValue = (NSValue*)[NSNumber numberWithBool:YES];
        //NSDictionary *op = [NSDictionary dictionaryWithObject:wrappedValue forKey:@"AVURLAssetPreferPreciseDurationAndTimingKey"];
       
        //AVAsset *a = [AVURLAsset URLAssetWithURL:URL options:op];
        //CMTime m = [a duration];
        //double dur = CMTimeGetSeconds(m);
        
        //NSLog(@"providesPreciseDurationAndTiming=%@", a.providesPreciseDurationAndTiming?@"YES":@"NO");
        
		//[mPlaybackView setPlayer:mPlayer];
		[mURL release];
		mURL = [URL retain];
		
        [self initPlayer];
			
		[mPlaybackView setPlayer:mPlayer];
		[self setup];
		//[mPlayer replaceCurrentItemWithPlayerItem:[AVPlayerItem playerItemWithURL:URL]];
        
         //[mPlaybackView setPlayer:mPlayer];
		//thumbnailView.image = [self setThumbnail];
		//if (watermark) {
			//[self syncWaterMark];
		//}
	}
}


-(void)setURLS:(NSArray *)URLS {
	if (urls != URLS) {
        NSLog(@"SETTING URLS FOR=%@", URLS);
		//[mPlaybackView setPlayer:mPlayer];
		[urls release];
		urls = [[NSArray arrayWithArray:URLS] retain];
		
		[self initQueuePlayer];
		
		[mPlaybackView setPlayer:mPlayer];
		[self setup];
		//[((AVQueuePlayer *)mPlayer replaceCurrentItemWithPlayerItem:[AVPlayerItem playerItemWithURL:URL]];
        
		//[mPlaybackView setPlayer:mPlayer];
		//thumbnailView.image = [self setThumbnail];
		//if (watermark) {
		//[self syncWaterMark];
		//}
	}
}

-(UIImage *)setThumbnail {
	AVURLAsset *avAsset = [AVURLAsset URLAssetWithURL:mURL options:nil];
	AVAssetImageGenerator *mImageGenerator = [[AVAssetImageGenerator allocWithZone:[self zone]] initWithAsset:avAsset];
	
	[mImageGenerator setAppliesPreferredTrackTransform:YES];
	[mImageGenerator setVideoComposition:[[mPlayer currentItem] videoComposition]];
	
	[mImageGenerator setMaximumSize:CGSizeMake(256, 256)];
	NSError *errorOut;
	CMTime actualTime;
	
	CGImageRef imgRef = [mImageGenerator copyCGImageAtTime:CMTimeMakeWithSeconds(0.5, NSEC_PER_SEC) actualTime:&actualTime error:&errorOut];
	UIImage *img = [UIImage imageWithCGImage:imgRef];
	return img;
}

-(void)syncWaterMark {
	if (mWatermarkObserver) {
		//NSLog(@"REMOVING OLD TIME OBSERVER");
		[mPlayer removeTimeObserver:mWatermarkObserver];
	}
	mWatermarkObserver = [[mPlayer addPeriodicTimeObserverForInterval:CMTimeMakeWithSeconds(0.01, NSEC_PER_SEC) queue:dispatch_get_main_queue() usingBlock:
						   ^(CMTime time) {
							   int dir1 = 1;
							   int dir2 = 1;
							   double rate = 0.1;
							   CGRect f1 = mPlaybackView.frame;
							   CGRect f2 = watermark.frame;
							   //NSLog(@"==================Frame1=%@, Frame2=%@ UIImage=%@",NSStringFromCGRect(f1), NSStringFromCGRect(f2), watermark);
							   watermark.center = CGPointMake(watermark.center.x +dir1*rate, watermark.center.y +dir2*rate);
							   if (!CGRectContainsRect(f1, f2)) {
								  
								   dir1 *= -1;//(arc4random() % 2 ? 1 : -1);
								   dir2 *= -1;//(arc4random() % 2 ? 1 : -1);
								   watermark.center = CGPointMake(watermark.center.x +10*(dir1*rate), watermark.center.y +10*(dir2*rate));
							   }
						   }] retain];
}

-(void)syncScrubber {
	AVPlayerItem* asset = mPlayer.currentItem;
	
	if (!asset)
		return;
	
	double duration = CMTimeGetSeconds(asset.duration);
	
	if (isfinite(duration) && duration > 0.0) {
		float minValue = [mScrubber minimumValue];
		float maxValue = [mScrubber maximumValue];
		double time = CMTimeGetSeconds(mPlayer.currentTime);
		//NSLog(@"time=%f",(maxValue - minValue) * time / duration + minValue);
		[mScrubber setValue:(maxValue - minValue) * time / duration + minValue animated:NO];
		//NSLog(@"Scrubber value = %6.2f", time);
		currentTime.text = [NSString stringWithFormat:@"%02.0f:%02.0f", time/60.0, fmodf(time, 60)];
		double rtime = duration - time;
		//NSLog(@"duration=%f, time=%f, rtime=%f", duration, time, rtime);
		remainingTime.text = [NSString stringWithFormat:@"-%02.0f:%02.0f", rtime/60.0, fmodf(rtime, 60)];
		//NSLog(@"%02.0f:%02.0f", time/60.0, time);
	}
	 
}

-(void)syncButtons {
	if ([self isPlaying]){
		
		[mPauseBar setHidden:NO];
		[mPlayBar setHidden:YES];
	} else {
		[mPauseBar setHidden:YES];
		[mPlayBar setHidden:NO];
	}
}

-(void)play:(id)sender {
    if (mURL != nil || urls != nil) {
        //[self initTimer];
        //[thumbnailView setHidden:YES];
        [mPlayer play];
    }
    
}

-(void)initTimer{
    //if (!theTimer) {
        //theTimer = [[NSTimer scheduledTimerWithTimeInterval:5.0 target:self selector:@selector(animateLogo) userInfo:nil repeats:YES] retain];
    //} else if(![theTimer isValid]) {
       // [theTimer release];
        //theTimer = [[NSTimer scheduledTimerWithTimeInterval:5.0 target:self selector:@selector(animateLogo) userInfo:nil repeats:YES] retain];
    //}
}

-(void)animateLogo {
    //NSLog(@"Timmer running");
    /*
    if (watermark.alpha == 1.0) {
        //NSLog(@"Timmer running-1");
        [UIView animateWithDuration:3.0 animations:^{ watermark.alpha = 0.0;}];
    } else if (watermark.alpha == 0.0) {
        //NSLog(@"Timmer running-2");
        [UIView animateWithDuration:3.0 animations:^{ watermark.alpha = 1.0;}];
    }
    */
}

-(void)pause:(id)sender {
    //NSLog(@"Timer invalidated");
    //[theTimer invalidate];
    //watermark.alpha = 1.0;
	[mPlayer pause];
}

-(BOOL)isPlaying {
	return mRestoreAfterScrubbingRate != 0.0f || [mPlayer rate] != 0.0f;
}

-(void)beginScrubbing:(id)sender {
	mRestoreAfterScrubbingRate = [mPlayer rate];
	[mPlayer setRate:0.0f];
	
	if (mTimeObserver) {
		[mPlayer removeTimeObserver:mTimeObserver];
		//dispatch_sync(dispatch_get_main_queue(), ^{});
		[mTimeObserver release];
		mTimeObserver = nil;
	}
}

-(double)getCurrentTime {
	return CMTimeGetSeconds([mPlayer currentTime]);
}

-(void)setScrubberToTime:(double)time {
	if (!thumbnailView.hidden) {
		thumbnailView.hidden = YES;
	}
	AVPlayerItem* asset = mPlayer.currentItem;
	
	if (!asset)
		return;
	
	double duration = CMTimeGetSeconds(asset.duration);
	
	if (isfinite(duration)) {
		//float minValue = [mScrubber minimumValue];
		//float maxValue = [mScrubber maximumValue];
		
		//float value = [mScrubber value];
		CGFloat width = CGRectGetWidth([mScrubber bounds]);
		
		//double time = duration * (value - minValue) / (maxValue - minValue);
		// time = dur *value
		//float v = time/duration;
		double tolerance = 0.0001f * duration / width;
		
		[mPlayer seekToTime:CMTimeMakeWithSeconds(time, NSEC_PER_SEC) toleranceBefore:CMTimeMakeWithSeconds(tolerance, NSEC_PER_SEC) toleranceAfter:CMTimeMakeWithSeconds(tolerance, NSEC_PER_SEC)];
	}
	
}

-(void)scrub:(id)sender {
	if ([sender isKindOfClass:[UISlider class]]) {
		UISlider* slider = sender;
		AVPlayerItem* asset = mPlayer.currentItem;
       
		
		if (!asset)
			return;
        
		double duration = CMTimeGetSeconds(asset.duration);
        //NSLog(@"SCRUB DURATION = %f", duration);
        
		
		if (isfinite(duration)) {
            //NSLog(@"SCRUBING duration=%f", duration);
			float minValue = [slider minimumValue];
			float maxValue = [slider maximumValue];
			
			float value = [slider value];
			CGFloat width = CGRectGetWidth([slider bounds]);
			
			double time = duration * (value - minValue) / (maxValue - minValue);
			double tolerance = 0.01f * duration / width;
			
			[mPlayer seekToTime:CMTimeMakeWithSeconds(time, NSEC_PER_SEC) toleranceBefore:CMTimeMakeWithSeconds(tolerance, NSEC_PER_SEC) toleranceAfter:CMTimeMakeWithSeconds(tolerance, NSEC_PER_SEC)];
		}
	}
}

-(void)endScrubbing:(id)sender {
	if (!mTimeObserver) {
		AVPlayerItem* asset = mPlayer.currentItem;
		
		if (!asset)
			return;
		
		double duration = CMTimeGetSeconds([asset duration]);
		
		if (isfinite(duration)) {
			CGFloat width = CGRectGetWidth([mScrubber bounds]);
			double tolerance = 0.01f * duration / width;
			NSLog(@"Tolerancef for player is =%f", tolerance);
			mTimeObserver = [[mPlayer addPeriodicTimeObserverForInterval:CMTimeMakeWithSeconds(tolerance, NSEC_PER_SEC) queue:dispatch_get_main_queue() usingBlock:
							  ^(CMTime time)
							  {
								  [self syncScrubber];
							  }] retain];
		}
	}
	
	if (mRestoreAfterScrubbingRate) {
		[mPlayer setRate:mRestoreAfterScrubbingRate];
		mRestoreAfterScrubbingRate = 0.f;
	}
}

-(BOOL)isScrubbing {
	return mRestoreAfterScrubbingRate != 0.f;
}

-(void)showLoadingAlertView {
	NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:@"VideoLoadingStatusView" owner:self options:nil];;
	VideoLoadingStatusView *statusView = (VideoLoadingStatusView *) [topLevelObjects objectAtIndex:0];
	statusView.center = mPlaybackView.center;
	statusView.tag = 9999;
	[mPlaybackView addSubview:statusView];
}


-(void)observeValueForKeyPath:(NSString*) path ofObject:(id)object change:(NSDictionary*)change context:(void*)context {
	if (context == VideoPlaybackViewDelegateRateObservationContext) {
		dispatch_async(dispatch_get_main_queue(),
					   ^{
						   [self syncButtons];
					   });
	} else if (context == VideoPlaybackViewDelegateDurationObservationContext) {
		dispatch_async(dispatch_get_main_queue(),
					   ^{
						   [self syncScrubber];
					   });
	} else if (context == VideoPlaybackViewDelegateStatusContext) {
		AVPlayer *ap = (AVPlayer *)object;
		
		if (ap.currentItem.status == AVPlayerItemStatusReadyToPlay) {
            NSLog(@"AVPlayer.currentItem.status=AVPlayerItemStatusReadyToPlay");
            [self play:self];
			dispatch_async(dispatch_get_main_queue(),
						   ^{
							  UIView *v = [mPlaybackView viewWithTag:9999];
                              [v removeFromSuperview];
						   });
		} else if (ap.currentItem.status == AVPlayerItemStatusFailed) {
			NSLog(@"AVPlayer.currentItem.status=AVPlayerItemStatusFailed => %@",ap.currentItem.error);
			dispatch_async(dispatch_get_main_queue(),
						   ^{
                               UIView *v = [mPlaybackView viewWithTag:9999];
                               [v removeFromSuperview];
							   [[[[UIAlertView alloc] initWithTitle:nil message:@"Video cannot be played failed to load from source" delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil] autorelease] show];
						   });
		} else if (ap.currentItem.status == AVPlayerItemStatusUnknown) {
            NSLog(@"AVPlayer.currentItem.status=AVPlayerItemStatusUnknown => %@", ap.currentItem.error);
            //if (retryCount == 0) {
                //NSLog(@"AVPlayerItemStatusUnknown received will try again");
                //[self initPlayer];
                //[mPlaybackView setPlayer:mPlayer];
                //[self setup];
                //retryCount++;
            //} else {
                //retryCount = 0;
                dispatch_async(dispatch_get_main_queue(),
						   ^{
                               UIView *v = [mPlaybackView viewWithTag:9999];
                               [v removeFromSuperview];
							  // [[[[UIAlertView alloc] initWithTitle:nil message:@"Video cannot be played status unknow." delegate:nil cancelButtonTitle:@"OK" otherButtonTitles:nil] autorelease] show];
						   });
            //}
        }
		
	} else {
		[super observeValueForKeyPath:path ofObject:object change:change context:context];
	}
}
@end 
