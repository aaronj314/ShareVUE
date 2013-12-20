//
//  VideoPlaybackListViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "BaseTableViewController.h"

@interface VideoPlaybackListViewController : BaseTableViewController {
	NSMutableArray *playlistItems;
	UITextField *playlistName;
	Playlist *playlist;
	Project *project;
	UIView *titleWrapper;
}

@property (nonatomic, retain) UIView *titleWrapper;
@property (nonatomic, retain) NSMutableArray *playlistItems;
@property (nonatomic, retain) Playlist *playlist;
@property (nonatomic, retain) Project *project;

-(void)editPlaylist:(id)sender;
@end
