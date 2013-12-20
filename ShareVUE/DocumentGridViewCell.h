//
//  DocumentGridViewCell.h
//  ShareVUE
//
//  Created by Darren Mason on 3/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AQGridViewCell.h"

@interface DocumentGridViewCell : AQGridViewCell {
    Project *project;
	UIView *iconView;
	UILabel *name;
}
@property (nonatomic, retain) Project *project;
@property (nonatomic, retain) IBOutlet UIView *iconView;
@property (nonatomic, retain) IBOutlet UILabel *name;
@end
