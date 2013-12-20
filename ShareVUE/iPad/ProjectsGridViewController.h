//
//  ProjectsGridViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridView.h"

@class ProjectGridViewCell;

@interface ProjectsGridViewController : UIViewController <AQGridViewDataSource, AQGridViewDelegate, UIGestureRecognizerDelegate>{
	AQGridView *gridView;
	NSMutableArray *projects;
    
    NSUInteger emptyCellIndex;
    
    NSUInteger dragOriginIndex;
    CGPoint dragOriginCellOrigin;
    
    ProjectGridViewCell *draggingCell;
	
	UIBarButtonItem *signOutButton;
}
@property (nonatomic, retain) IBOutlet AQGridView *gridView;
@property (nonatomic, retain) IBOutlet UIBarButtonItem *signOutButton;
@property (nonatomic, retain) NSMutableArray *projects;

-(void)loadProjectsFromService;

@end
