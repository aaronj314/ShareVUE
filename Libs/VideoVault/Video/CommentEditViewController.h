//
//  CommentEditViewController.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface CommentEditViewController : UIViewController {
	UIViewController *modalController;
	IBOutlet UITextView *comment;
	IBOutlet UILabel *timecode;
}
@property (nonatomic, retain) UIViewController *modalController;
@property (nonatomic, retain) UILabel *timecode;
@property (nonatomic, retain) UITextView *comment;
-(IBAction)done:(id)sender;
@end
