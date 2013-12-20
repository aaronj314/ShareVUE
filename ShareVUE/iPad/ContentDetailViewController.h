//
//  ProjectDetailViewController_iPad.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/29/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ContentDetailViewController.h"
#import "MGSplitViewController.h"

@interface ContentDetailViewController : UIViewController <UIPopoverControllerDelegate, MGSplitViewControllerDelegate> {
	UIPopoverController *popoverController;
    UIToolbar *toolbar;
    UIViewController *contentController;
}
@property (nonatomic, retain) UIToolbar *toolbar;
@property (nonatomic, retain) UIViewController *contentController;
@property (nonatomic, retain) UIPopoverController *popoverController;

-(void)setDetailItem:(id)newDetailItem;
-(void)configureView;
-(void)addTitle:(NSString *)title;
@end
