//
//  PlayPlaylistButton.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlayPlaylistButton.h"



@implementation PlayPlaylistButton
@synthesize playlist;

- (id)initWithFrame:(CGRect)frame {
    
    self = [super initWithFrame:frame];
    if (self) {
        // Initialization code.
    }
    return self;
}

/*
// Only override drawRect: if you perform custom drawing.
// An empty implementation adversely affects performance during animation.
- (void)drawRect:(CGRect)rect {
    // Drawing code.
}
*/

- (void)dealloc {
	[playlist release];
    [super dealloc];
}
 

@end
 