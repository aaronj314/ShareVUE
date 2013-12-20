//
//  ProjectVideosGridCell.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ProjectVideosGridViewCell.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "SourceVideo.h"
#import "AsyncUIImageView.h"
#import <QuartzCore/QuartzCore.h>

@implementation ProjectVideosGridViewCell
@synthesize name;
@synthesize iconView;
@synthesize thumbnailView;
@synthesize downloadVideoButton;

- (void) dealloc {
    [downloadVideoButton release];
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
    
     
    
    static NSString *kCellNibName = @"ProjectVideosGridViewCell";
	NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:self options:nil];
	iconView = [[topLevelObjects objectAtIndex:0] retain];
    downloadVideoButton = [[iconView viewWithTag:3] retain];
    
   
    [downloadVideoButton addTarget:self action:@selector(downloadVideo:) forControlEvents:UIControlEventTouchUpInside];
    //iconView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"project.png"]];
    
    /* UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:iconView.frame cornerRadius: 18.0];
     iconView.layer.shadowPath = path.CGPath;
     iconView.layer.shadowRadius = 20.0;
     iconView.layer.shadowOpacity = 0.4;
     iconView.layer.shadowOffset = CGSizeMake( 20.0, 20.0 );
     */
    thumbnailView.layer.cornerRadius = 5.0;
	[self.contentView addSubview:iconView];
    self.contentView.clipsToBounds = YES;
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

-(IBAction)downloadVideo:(id)sender {
    NSLog(@"download hit");
    NSArray *path = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
	NSString *docDirectory = [path objectAtIndex:0];
    NSLog(docDirectory);
	NSString *file = [docDirectory stringByAppendingPathComponent:@"save.iDK"];
	NSLog(file);
    //ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    //appDelegate.account;
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
