//
//  ProjectMaterialsGridViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 3/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridView.h"

@class DocumentGridViewCell;
@class VideoPlayFullViewController;
@class ContentDetailViewController;

@interface ProjectMaterialsGridViewController : UIViewController <AQGridViewDataSource, AQGridViewDelegate, UIGestureRecognizerDelegate> {
	AQGridView *gridView;
	NSMutableArray *materials;
    
    NSUInteger emptyCellIndex;
    
    NSUInteger dragOriginIndex;
    CGPoint dragOriginCellOrigin;
    
    DocumentGridViewCell *draggingCell;
	UISegmentedControl *segmentControl;
	UILabel *projectName;
	
	VideoPlayFullViewController *videoFullViewController;
	ContentDetailViewController *contentDetailViewController;
}

@property (nonatomic,retain) IBOutlet UILabel *projectName;
@property (nonatomic, retain) Project *project;
@property (nonatomic, retain) IBOutlet AQGridView *gridView;
@property (nonatomic, retain) IBOutlet UISegmentedControl *segmentControl;
@property (nonatomic, retain) NSMutableArray *materials;
@property(nonatomic, retain) ContentDetailViewController *contentDetailViewController;
@end
