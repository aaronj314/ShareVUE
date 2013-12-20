/*
 * AQGridViewUpdateInfo.h
 * AQGridView
*/
//  Created by Aaron Jones on 1/4/11.

#import <Foundation/Foundation.h>
#import "AQGridViewUpdateItem.h"
#import "AQGridView.h"

// used internally by AQGridView and AQGridViewUpdateInfo
@interface AQGridView ()
@property (nonatomic, copy) NSSet * animatingCells;
@end

@interface AQGridViewUpdateInfo : NSObject
{
	// NB: These are never cleared, only sorted & modified.
	// It is assumed that a deferred update info object will be created in -beginUpdates
	//  and released in -endUpdates, and will not need to last across multiple suspended update sequences
	NSMutableArray *	_insertItems;
	NSMutableArray *	_deleteItems;
	NSMutableArray *	_moveItems;
	NSMutableArray *	_reloadItems;
	
	// index sets, cached for handiness
	NSMutableIndexSet * _insertedIndices;
	NSMutableIndexSet *	_deletedIndices;
	NSMutableIndexSet * _oldMovedIndices;
	NSMutableIndexSet * _newMovedIndices;
	NSMutableIndexSet * _reloadedIndices;
	
	// old and new grid data -- for bounds calculations
	AQGridViewData *	_oldGridData;
	AQGridViewData *	_newGridData;
	
	// mapping tables, used to map from old indices to new ones
	NSUInteger *		_oldToNewIndexMap;
	NSUInteger *		_newToOldIndexMap;
	
	// indices of all items which were simply shuffled around as a result of other operations
	NSMutableIndexSet *	_onlyMovedIndices;
	
	// needs to ask the grid view for cells
	AQGridView *		_gridView;		// weak reference
	
	NSMutableSet *		_animatingCells;
}

- (id) initWithOldGridData: (AQGridViewData *) oldGridData forGridView: (AQGridView *) gridView;

- (void) updateItemsAtIndices: (NSIndexSet *) indices
				 updateAction: (AQGridViewUpdateAction) action
				withAnimation: (AQGridViewItemAnimation) animation;
- (void) moveItemAtIndex: (NSUInteger) index
				 toIndex: (NSUInteger) index
		   withAnimation: (AQGridViewItemAnimation) animation;

@property (nonatomic, readonly) NSUInteger numberOfUpdates;

// This function assumed a certain ordering in which items will be inserted/deleted etc.
// Specifically, it will assume deletions happen FIRST, then insertions SECOND, and reloads LAST.
// The indices provided are all assumed to refer to the content index set as it existed prior
//  to ANY inserts/deletes occurring.
// Needless to say: this is therefore quite private, since AQGridView must conform to and rely
//  on this behaviour
- (void) cleanupUpdateItems;

// the returned values are not guaranteed to be correct prior to invocation of -cleanupUpdateItems above
- (NSArray *) sortedInsertItems;
- (NSArray *) sortedDeleteItems;
- (NSArray *) sortedMoveItems;
- (NSArray *) sortedReloadItems;

- (AQGridViewData *) newGridViewData;
- (NSUInteger) numberOfItemsAfterUpdates;

- (NSUInteger) newIndexForOldIndex: (NSUInteger) oldIndex;

// returns a list of all the views being animated
- (NSSet *) animateCellUpdatesUsingVisibleContentRect: (CGRect) contentRect;

@end
