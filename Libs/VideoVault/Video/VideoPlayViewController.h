//
//  VideoPlayViewController.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/29/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class SourceVideo;
@class VideoPlaybackCommentDelegate;
@class VideoPlaybackView;
@class VideoPlayFullViewController;
@class PlayerCommentSliderView;

@interface VideoPlayViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> {
	SourceVideo *video;
	
	UITableView *tableView;
	IBOutlet VideoPlaybackCommentDelegate *playbackDelegate;
	VideoPlayFullViewController *videoFullViewController;
	BOOL wasPlaying;
	PlayerCommentSliderView *slider;
	IBOutlet UIView *playButton;
	IBOutlet UIView *pauseButton;
	
	IBOutlet UIImageView *watermark;
	IBOutlet UILabel *uuidWaterMark;
	IBOutlet UILabel *userWaterMark;
	
	IBOutlet UISegmentedControl *segmentedControl;
	
	//Video meta data
	IBOutlet UIView *videoMetaData;
	
	IBOutlet VideoPlaybackView *playbackView;
    
    IBOutlet UIBarButtonItem *editButton;
    UIView *titlePanel;
    UIView *editBar;
    
    UILabel *currentTime;
    UILabel *remainingTime;
    
}
@property (nonatomic, retain) SourceVideo *video;
@property (nonatomic, retain) IBOutlet UITableView *tableView;
@property (nonatomic, retain) VideoPlaybackCommentDelegate *playbackDelegate;
@property (nonatomic,retain) IBOutlet PlayerCommentSliderView *slider;
@property (nonatomic, retain) IBOutlet VideoPlaybackView *playbackView;
@property (nonatomic, retain) IBOutlet UIView *titlePanel;

@property (nonatomic, retain) IBOutlet UILabel *currentTime;
@property (nonatomic, retain) IBOutlet UILabel *remainingTime;

-(IBAction)fullScreen:(id)sender;
-(IBAction)minScreen:(id)sender;
-(IBAction)addCommentForTimecode:(id)sender;
-(IBAction)segmentedControlIndexChanged:(id)sender;
-(IBAction)editComments:(id)sender;
@end
