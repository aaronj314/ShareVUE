

//  Created by Aaron Jones on 1/4/11.

#import <Foundation/Foundation.h>
#import "AQGridView.h"

typedef enum {
	AQGridViewUpdateActionInsert,
	AQGridViewUpdateActionDelete,
	AQGridViewUpdateActionMove,
	AQGridViewUpdateActionReload
} AQGridViewUpdateAction;

@interface AQGridViewUpdateItem : NSObject
{
	NSUInteger				_index;
	NSUInteger				_newIndex;
	AQGridViewUpdateAction	_action;
	AQGridViewItemAnimation	_animation;
	NSInteger				_offset;
}

- (id) initWithIndex: (NSUInteger) index action: (AQGridViewUpdateAction) action animation: (AQGridViewItemAnimation) animation;

- (NSComparisonResult) compare: (AQGridViewUpdateItem *) other;
- (NSComparisonResult) inverseCompare: (AQGridViewUpdateItem *) other;

@property (nonatomic, readonly) NSUInteger index;
@property (nonatomic) NSUInteger newIndex;		// only valid for AQGridViewUpdateActionMove
@property (nonatomic, readonly) AQGridViewUpdateAction action;
@property (nonatomic, readonly) AQGridViewItemAnimation animation;

// this is an offset to apply to the index, due to other changes in the list which occurred since this index was chosen
@property (nonatomic) NSInteger offset;
@property (nonatomic, readonly) NSUInteger originalIndex;	// returns index without offset

@end
