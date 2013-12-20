//
//  AQGridViewAnimatorItem.h
//  
//
//  Created by Aaron Jones on 1/4/11.
//

#import <UIKit/UIKit.h>

@interface AQGridViewAnimatorItem : NSObject

+ (AQGridViewAnimatorItem *) itemWithView: (UIView *) aView index: (NSUInteger) anIndex;

@property (nonatomic, retain) UIView * animatingView;	// probably an AQGridViewCell, maybe a UIImageView
@property (nonatomic, assign) NSUInteger index;			// the DESTINATION index -- use NSNotFound if this is being deleted

- (NSUInteger) hash;
- (BOOL) isEqual: (AQGridViewAnimatorItem *) o;
- (NSComparisonResult) compare: (id) obj;

@end
