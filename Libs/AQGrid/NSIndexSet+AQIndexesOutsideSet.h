//
//  NSIndexSet+AQIndexesOutsideSet.h
//  Created by Aaron Jones on 1/4/11.

#import <Foundation/NSIndexSet.h>

@interface NSIndexSet (AQIndexesOutsideSet)
- (NSIndexSet *) aq_indexesOutsideIndexSet: (NSIndexSet *) otherSet;
@end
