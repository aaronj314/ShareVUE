//
//  CreatePlaylistVideoGridViewCell.m
//  ShareVUE
//
//  Created by Aaron Jones on 3/3/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#import "CreatePlaylistVideoGridViewCell.h"
#import "AsyncUIImageView.h"
#import <QuartzCore/QuartzCore.h>

@implementation CreatePlaylistVideoGridViewCell

@synthesize name;
@synthesize iconView;
@synthesize thumbnailView;

- (void) dealloc
{
    [thumbnailView release];
    [iconView release];
	[name release];
	[video release];
	[super dealloc];
}

- (id) initWithFrame:(CGRect)frame reuseIdentifier:(NSString *) reuseIdentifier {
    self = [super initWithFrame: frame reuseIdentifier: reuseIdentifier];
    if ( self == nil )
        return ( nil );
    
    
    
    static NSString *kCellNibName = @"CreatePlaylistVideoGridViewCell";
	NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:self options:nil];
	iconView = [[topLevelObjects objectAtIndex:0]retain];
    
    //iconView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"project.png"]];
    
    /* UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:iconView.frame cornerRadius: 18.0];
     iconView.layer.shadowPath = path.CGPath;
     iconView.layer.shadowRadius = 20.0;
     iconView.layer.shadowOpacity = 0.4;
     iconView.layer.shadowOffset = CGSizeMake( 20.0, 20.0 );
     */
    thumbnailView.layer.cornerRadius = 5.0;
	[self.contentView addSubview:iconView];
    self.contentView.backgroundColor = [UIColor clearColor];
    self.backgroundColor = [UIColor clearColor];
    
    self.contentView.opaque = NO;
    self.opaque = NO;
    
    self.selectionStyle = AQGridViewCellSelectionStyleGlow;
    
    return ( self );
}
-(SourceVideo *)video {
	return video;
}

-(void)setVideo:(SourceVideo *)vid {
	if (video != vid) {
		SourceVideo *tmp = video;
		video = [vid retain];
		[tmp release];
		name.text = video.name;
        [thumbnailView imageViewFromURL:video.thumbnailUrl];
	}
}



@end
