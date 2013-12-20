//
//  ProjectGridViewCell.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ProjectGridViewCell.h"
#import <QuartzCore/QuartzCore.h>


@implementation ProjectGridViewCell
@synthesize name;
@synthesize iconView;

- (id) initWithFrame:(CGRect)frame reuseIdentifier:(NSString *) reuseIdentifier {
    self = [super initWithFrame: frame reuseIdentifier: reuseIdentifier];
    if ( self == nil )
        return ( nil );
    
    
    
    static NSString *kCellNibName = @"ProjectGridViewCell";
	NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:self options:nil];
	iconView = [[topLevelObjects objectAtIndex:0]retain];
    
    //iconView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"project.png"]];

   /* UIBezierPath *path = [UIBezierPath bezierPathWithRoundedRect:iconView.frame cornerRadius: 18.0];
    iconView.layer.shadowPath = path.CGPath;
    iconView.layer.shadowRadius = 20.0;
    iconView.layer.shadowOpacity = 0.4;
    iconView.layer.shadowOffset = CGSizeMake( 20.0, 20.0 );
	*/
	[self.contentView addSubview:iconView];
    self.contentView.backgroundColor = [UIColor clearColor];
    self.backgroundColor = [UIColor clearColor];
    
    self.contentView.opaque = NO;
    self.opaque = NO;
    
    self.selectionStyle = AQGridViewCellSelectionStyleGlow;
    
    return ( self );
}
-(Project *)project {
	return project;
}

-(void)setProject:(Project *)prj {
	if (project != prj) {
		Project *tmp = project;
		project = [prj retain];
		[tmp release];
		name.text = project.name;
	}
}

- (void) dealloc
{
    [iconView release];
	[name release];
	[project release];
	[super dealloc];
}

@end
