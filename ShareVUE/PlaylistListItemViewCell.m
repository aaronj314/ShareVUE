//
//  PlaylistListItemViewCell.m
//  ShareVUE
//
//  Created by Darren Mason on 2/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlaylistListItemViewCell.h"
#import "AsyncUIImageView.h"
#import "PlayPlaylistButton.h"

@implementation PlaylistListItemViewCell
@synthesize title;
@synthesize date;
@synthesize durration;
@synthesize thumbnail;
@synthesize commentCount;
@synthesize playPlaylistButton;
@synthesize loadingStatus;

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
	[loadingStatus release];
	[playPlaylistButton release];
	[commentCount release];
	[title release];
	[date release];
	[durration release];
	[thumbnail release];
    [super dealloc];
}

@end
