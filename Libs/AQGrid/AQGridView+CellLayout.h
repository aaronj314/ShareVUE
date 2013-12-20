

 //  Created by Aaron Jones on 1/4/11.

#import <UIKit/UIKit.h>
#import "AQGridView.h"

// used by AQGridViewUpdateInfo
@interface AQGridView (AQCellLayout)
- (CGRect) fixCellFrame: (CGRect) cellFrame forGridRect: (CGRect) gridRect;
- (void) updateGridViewBoundsForNewGridData: (AQGridViewData *) newGridData;
- (AQGridViewCell *) createPreparedCellForIndex: (NSUInteger) index;
- (AQGridViewCell *) createPreparedCellForIndex: (NSUInteger) index usingGridData: (AQGridViewData *) gridData;
- (void) insertVisibleCell: (AQGridViewCell *) cell atIndex: (NSUInteger) visibleCellListIndex;
- (void) deleteVisibleCell: (AQGridViewCell *) cell atIndex: (NSUInteger) visibleCellListIndex appendingNewCell: (AQGridViewCell *) newCell;
- (void) ensureCellInVisibleList: (AQGridViewCell *) cell;
- (void) animationWillRevealItemsAtIndices: (NSRange) indices;
@end
