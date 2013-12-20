//
//  NSIndexSet+AQIsSetContiguous.m
//  AQGridView
//  Created by Aaron Jones on 1/4/11.

#import "NSIndexSet+AQIsSetContiguous.h"

@implementation NSIndexSet (AQIsSetContiguous)

- (BOOL) aq_isSetContiguous
{
    return ( (([self lastIndex] - [self firstIndex]) + 1) == [self count] );
}

@end
