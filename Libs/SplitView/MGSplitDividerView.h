//
//  MGSplitDividerView.h
//  MGSplitView
//
//  Created by Aaron Jones on 1/8/11.
//


#import <UIKit/UIKit.h>

@class MGSplitViewController;
@interface MGSplitDividerView : UIView {
	MGSplitViewController *splitViewController;
	BOOL allowsDragging;
}

@property (nonatomic, assign) MGSplitViewController *splitViewController; // weak ref.
@property (nonatomic, assign) BOOL allowsDragging;

- (void)drawGripThumbInRect:(CGRect)rect;

@end
