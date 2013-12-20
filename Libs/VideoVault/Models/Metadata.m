//
//  Metadata.m
//  ShareVUE
//
//  Created by Aaron Jones on 4/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Metadata.h"


@implementation SMetadata
@synthesize name, value, metadataId;
- (void)dealloc {
    [metadataId release];
    [name release];
    [value release];
    [super dealloc];
}
@end
