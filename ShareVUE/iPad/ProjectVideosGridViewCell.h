//
//  ProjectVideosGridCell.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AQGridViewCell.h"

@class SourceVideo;
@class AsyncUIImageView;

@interface ProjectVideosGridViewCell : AQGridViewCell {
    SourceVideo *video;
	UIView *iconView;
	UITextView *name;
	AsyncUIImageView *thumbnailView;
    UIButton *downloadVideoButton;
}
@property (nonatomic, retain) SourceVideo *video;
@property (nonatomic, retain) UIView *iconView;
@property (nonatomic, retain) IBOutlet UITextView *name;
@property (nonatomic, retain) IBOutlet AsyncUIImageView *thumbnailView;
@property (nonatomic, retain) UIButton *downloadVideoButton;

@end
