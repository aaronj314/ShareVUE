//
//  ProjectVideoListViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 3/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#import <Foundation/Foundation.h>
#import "BaseTableViewController.h"

@interface ProjectVideoListViewController : BaseTableViewController {
	NSMutableArray *videos;
	UITextField *playlistName;
	Project *project;
	UIView *titleWrapper;
}

@property (nonatomic, retain) UIView *titleWrapper;
@property (nonatomic, retain) NSMutableArray *videos;
@property (nonatomic, retain) Project *project;

@end
