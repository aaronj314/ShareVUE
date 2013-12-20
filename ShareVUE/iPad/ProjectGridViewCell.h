//
//  ProjectGridViewCell.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridViewCell.h"

@interface ProjectGridViewCell : AQGridViewCell {
    Project *project;
	UIView *iconView;
	UITextView *name;
	
}
@property (nonatomic, retain) Project *project;
@property (nonatomic, retain) IBOutlet UIView *iconView;
@property (nonatomic, retain) IBOutlet UITextView *name;
@end


