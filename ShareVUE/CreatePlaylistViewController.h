//
//  CreatePlaylistViewController.h
//  ShareVUE
//
//  Created by Darren Mason on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridView.h"

@class CreatePlaylistVideoGridViewCell;

@interface CreatePlaylistViewController : UIViewController <UITableViewDelegate, UITableViewDataSource, AQGridViewDataSource, AQGridViewDelegate, UIGestureRecognizerDelegate> {
	id delegate;
	Project *project;
	Playlist *playlist;
	UIView *titlePanel;
	UITextField *playlistName;
	UISwitch *shared;
	NSMutableArray *playlistItems;
	AQGridView *gridView;
	UITableView *tableView;
	
	NSMutableArray *videos;
    
    NSUInteger emptyCellIndex;
    
    NSUInteger dragOriginIndex;
    CGPoint dragOriginCellOrigin;
	CreatePlaylistVideoGridViewCell *draggingCell;
	
	@public
	BOOL editing;
}
@property (nonatomic, retain) id delegate;
@property (nonatomic, retain) Project *project;
@property (nonatomic, retain) Playlist *playlist;
@property (nonatomic, retain) IBOutlet UITextField *playlistName;
@property (nonatomic, retain) IBOutlet UISwitch *shared;
@property (nonatomic, retain) IBOutlet UIView *titlePanel;
@property (nonatomic, retain) IBOutlet AQGridView *gridView;
@property (nonatomic, retain) IBOutlet UITableView *tableView;
@property (nonatomic, retain) NSMutableArray *playlistItems;
@property (nonatomic, retain) NSMutableArray *videos;

-(IBAction)savePlaylist:(id)sender;
-(IBAction)cancel:(id)sender;
@end
