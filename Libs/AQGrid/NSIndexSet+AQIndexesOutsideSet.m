//
//  NSIndexSet+AQIndexesOutsideSet.m
//  Created by Aaron Jones on 1/4/11.

#import <Foundation/Foundation.h>
#import "NSIndexSet+AQIndexesOutsideSet.h"

@implementation NSIndexSet (AQIndexesOutsideSet)

- (NSIndexSet *) aq_indexesOutsideIndexSet: (NSIndexSet *) otherSet
{
	NSMutableIndexSet * mutable = [self mutableCopy];
	[mutable removeIndexes: otherSet];
	NSIndexSet * result = [mutable copy];
	[mutable release];
	return ( [result autorelease] );
}

@end
