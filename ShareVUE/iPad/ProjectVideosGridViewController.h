//
//  ProjectVideosGridViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridView.h"


@class ProjectVideosGridViewCell;
@class VideoPlayFullViewController;
@class ContentDetailViewController;
@class ProjectMaterialsGridView;
@class FilterSelectViewController;

@interface ProjectVideosGridViewController : UIViewController <AQGridViewDataSource, AQGridViewDelegate, UIGestureRecognizerDelegate, UITextFieldDelegate>{
	AQGridView *gridView;
    ProjectMaterialsGridView *materialsGridView;
    Project *project;
	NSMutableArray *videos;
    
    NSUInteger emptyCellIndex;
    
    NSUInteger dragOriginIndex;
    CGPoint dragOriginCellOrigin;
    
    ProjectVideosGridViewCell *draggingCell;
	UISegmentedControl *segmentControl;
	UIBarButtonItem *signOutButton;
	UILabel *projectName;
	
	VideoPlayFullViewController *videoFullViewController;
	ContentDetailViewController *contentDetailViewController;
    
    //ALE Filter UI
    UITextField *aleKeySelectBox;
    UITextField *aleValueSelectBox;
    FilterSelectViewController *filterSelectViewController;
    
}

@property (nonatomic,retain) IBOutlet UILabel *projectName;
@property (nonatomic, retain) Project *project;
@property (nonatomic, retain) IBOutlet AQGridView *gridView;
@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentControl;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *signOutButton;
@property (nonatomic, retain) NSMutableArray *videos;
@property (nonatomic, retain) ContentDetailViewController *contentDetailViewController;

@property (nonatomic, retain) IBOutlet UITextField *aleKeySelectBox;
@property (nonatomic, retain) IBOutlet UITextField *aleValueSelectBox;
@property (nonatomic, retain) FilterSelectViewController *filterSelectViewController;

-(void)loadVideosFromService;
-(void)loadVideosForPlaylist:(Playlist *)playlist;
-(IBAction)switchGridView:(id)sender;
@end