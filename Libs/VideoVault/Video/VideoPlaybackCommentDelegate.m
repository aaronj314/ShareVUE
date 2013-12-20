//
//  VideoPlaybackCommentDelegate.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import <AVFoundation/AVFoundation.h>
#import "VideoPlaybackCommentDelegate.h"
#import "PlayerCommentSliderView.h"

static NSString* const VideoPlaybackViewDelegateLoadedTimeRangesContext = @"VideoPlaybackViewDelegateLoadedTimeRangesContext";

@implementation VideoPlaybackCommentDelegate
@synthesize commentBox, commentSlider;

-(void)dealloc {
	//NSLog(@"dealloc::%@", [self class]);
	[commentSlider release];
	[commentBox release];
	[super dealloc];
}

-(void)setCommentSlider:(PlayerCommentSliderView *)cSlider {
	if (cSlider != commentSlider) {
		id tmp = commentSlider;
		commentSlider = [cSlider retain];
		[tmp release];
		self.mScrubber = cSlider.slider;
	}
	
}
/*
-(void)scrub:(id)sender {
	if ([sender isKindOfClass:[UISlider class]]) {
		UISlider* slider = sender;
		if (!thumbnailView.hidden) {
			thumbnailView.hidden = YES;
		}
		AVAsset* asset = [[mPlayer currentItem] asset];
		
		if (!asset)
			return;
		
		double duration = CMTimeGetSeconds([asset duration]);
		
		if (isfinite(duration)) {
			float minValue = [slider minimumValue];
			float maxValue = [slider maximumValue];
			//NSLog(@"min=%f, max=%f",minValue, maxValue);
			float value = [slider value];
			CGFloat width = CGRectGetWidth([slider bounds]);
			
			double time = duration * (value - minValue) / (maxValue - minValue);
			double tolerance = 0.5f * duration / width;
			
			[mPlayer seekToTime:CMTimeMakeWithSeconds(time, NSEC_PER_SEC) toleranceBefore:CMTimeMakeWithSeconds(tolerance, NSEC_PER_SEC) toleranceAfter:CMTimeMakeWithSeconds(tolerance, NSEC_PER_SEC)];
			
			
			

		}
		 
	}
}
*/
-(void)observeValueForKeyPath:(NSString*) path ofObject:(id)object change:(NSDictionary*)change context:(void*)context {
	if (context == VideoPlaybackViewDelegateLoadedTimeRangesContext) {
		AVPlayer *ap = (AVPlayer *)object;
		if (ap.currentItem.loadedTimeRanges && [ap.currentItem.loadedTimeRanges count] > 0) {
			//int idx = 0;
			for (NSValue *value in ap.currentItem.loadedTimeRanges) {
				CMTimeRange v = [value CMTimeRangeValue];
				//NSLog(@"%i--VideoPlaybackViewDelegateLoadedTimeRangesContext==%f,%f", [ap.currentItem.loadedTimeRanges count], CMTimeGetSeconds(v.duration), CMTimeGetSeconds(v.start));
				//idx++;
				double duration = CMTimeGetSeconds([ap.currentItem.asset duration]);
				double loaded = CMTimeGetSeconds(v.duration);
				double ld = loaded/duration;
				if (ld >= 0.9f) {
					ld = 1.0f;
				}
				
				//NSLog(@"duration=%f, loaded=%f, loaded/duration=%f",duration, loaded,ld);
				[commentSlider setProgressValue:ld];
			}
			
		}
	} else {
		[super observeValueForKeyPath:path ofObject:object change:change context:context];
	}
}
@end
