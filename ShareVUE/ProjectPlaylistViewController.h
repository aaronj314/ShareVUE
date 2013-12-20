//
//  ProjectPlaylistViewController.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BaseTableViewController.h"

@class Project;


@interface ProjectPlaylistViewController : BaseTableViewController {
	NSMutableArray *playlists;
	UITextField *projectName;
	Project *project;
	UIView *titleWrapper;
}
@property (nonatomic,retain) UIView *titleWrapper;
@property (nonatomic, retain) NSMutableArray *playlists;
@property (nonatomic, retain) Project *project;

-(void)addPlaylist:(id)sender;
@end
