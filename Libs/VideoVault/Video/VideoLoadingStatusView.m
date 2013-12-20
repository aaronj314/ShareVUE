//
//  VideoLoadingStatusView.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "VideoLoadingStatusView.h"


@implementation VideoLoadingStatusView
@synthesize spinner;

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
    [spinner stopAnimating];
    [spinner release];
    [super dealloc];
}


@end
