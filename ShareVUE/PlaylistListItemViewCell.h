//
//  PlaylistListItemViewCell.h
//  ShareVUE
//
//  Created by Darren Mason on 2/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AsyncUIImageView;
@class PlayPlaylistButton;

@interface PlaylistListItemViewCell : UITableViewCell {
	UILabel *title;
	UILabel *date;
	UILabel *durration;
	UILabel *commentCount;
	AsyncUIImageView *thumbnail;
	PlayPlaylistButton *playPlaylistButton;
	UIActivityIndicatorView *loadingStatus;
}
@property (nonatomic, retain) IBOutlet UILabel *title;
@property (nonatomic, retain) IBOutlet UILabel *date;
@property (nonatomic, retain) IBOutlet UILabel *durration;
@property (nonatomic, retain) IBOutlet UILabel *commentCount;
@property (nonatomic, retain) IBOutlet AsyncUIImageView *thumbnail;
@property (nonatomic, retain) IBOutlet PlayPlaylistButton *playPlaylistButton;
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *loadingStatus;

@end
