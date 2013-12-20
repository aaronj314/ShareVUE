//
//  VideoListItemViewCell.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class AsyncUIImageView;

@interface VideoListItemViewCell : UITableViewCell {
	UILabel *title;
	UILabel *date;
	UILabel *durration;
	UILabel *commentCount;
	AsyncUIImageView *thumbnail;
}
@property (nonatomic, retain) IBOutlet UILabel *title;
@property (nonatomic, retain) IBOutlet UILabel *date;
@property (nonatomic, retain) IBOutlet UILabel *durration;
@property (nonatomic, retain) IBOutlet UILabel *commentCount;
@property (nonatomic, retain) IBOutlet AsyncUIImageView *thumbnail;
@end
