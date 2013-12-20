//
//  VideoPlayFullViewController.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/30/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class VideoPlayControlsView;
@class VideoPlaybackCommentDelegate;
@class VideoPlaybackView;
@class SourceVideo;

@interface VideoPlayFullViewController : UIViewController <UITextViewDelegate> {
	UIToolbar *playButton;
	IBOutlet UIView *commentField;
	IBOutlet UITextView *commentText;
	IBOutlet VideoPlayControlsView *controlsView;
	IBOutlet VideoPlaybackCommentDelegate *playbackDelegate;
	id delegate;
	IBOutlet UIBarButtonItem *minScreenButton;
	IBOutlet UIView *thumbnail;
	//IBOutlet VideoPlaybackView *playbackView;
	
	IBOutlet UIImageView *watermark;
	IBOutlet UILabel *uuidWaterMark;
	IBOutlet UILabel *userWaterMark;
	
	SourceVideo *video;
    
    UIView *editBar;
}
@property (nonatomic, retain) IBOutlet UIToolbar *playButton;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *minScreenButton;
@property (nonatomic, retain) IBOutlet UILabel *uuidWaterMark, *userWaterMark;
@property (nonatomic, retain) IBOutlet UIImageView *watermark; 
@property (nonatomic, retain) id delegate;
@property (nonatomic, retain) VideoPlaybackCommentDelegate *playbackDelegate;
@property (nonatomic, retain) SourceVideo *video;

-(IBAction)addTimecodeComment:(id)sender;
-(IBAction)playVideo:(id)sender;
-(IBAction)pauseVideo:(id)sender;
-(IBAction)showControls:(id)sender;
-(void)loadPlayerView;
@end
