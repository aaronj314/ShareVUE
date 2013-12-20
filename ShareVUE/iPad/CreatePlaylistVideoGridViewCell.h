//
//  CreatePlaylistVideoGridViewCell.h
//  ShareVUE
//
//  Created by Aaron Jones on 3/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridViewCell.h"

@class AsyncUIImageView;

@interface CreatePlaylistVideoGridViewCell : AQGridViewCell {
    SourceVideo *video;
	UIView *iconView;
	UILabel *name;
	AsyncUIImageView *thumbnailView;
}
@property (nonatomic, retain) SourceVideo *video;
@property (nonatomic, retain) UIView *iconView;
@property (nonatomic, retain) IBOutlet UILabel *name;
@property (nonatomic, retain) IBOutlet AsyncUIImageView *thumbnailView;
@end
