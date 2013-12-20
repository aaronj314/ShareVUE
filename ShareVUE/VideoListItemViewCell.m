//
//  VideoListItemViewCell.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "VideoListItemViewCell.h"
#import "AsyncUIImageView.h"

@implementation VideoListItemViewCell
@synthesize title;
@synthesize date;
@synthesize durration;
@synthesize thumbnail;
@synthesize commentCount;

- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier {
    
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code.
    }
    return self;
}

-(id)initWithCoder:(NSCoder *)aDecoder {
	if ((self = [super initWithCoder:aDecoder])) {
		
	}
	
	return self;
}



- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    
    [super setSelected:selected animated:animated];
    
    // Configure the view for the selected state.
}


- (void)dealloc {
	[commentCount release];
	[title release];
	[date release];
	[durration release];
	[thumbnail release];
    [super dealloc];
}


@end
