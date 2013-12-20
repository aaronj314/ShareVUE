//
//  Asset.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Asset.h"
#import "Project.h"

@implementation Asset
@synthesize assetId, name, url, projectId;

#pragma mark -
#pragma mark DEMO CODE
+(NSMutableArray *)assetsForDemo {
	Asset *a1 = [[[Asset alloc] init] autorelease];
	a1.assetId = @"12345789";
	a1.name = @"Demo Asset 1";
	return [NSMutableArray arrayWithObjects:a1, nil];
}

- (void) dealloc {
	//NSLog(@"dealloc::%@", [self class]);
	[url release];
	[projectId release];
	[assetId release];
	[name release];
	[super dealloc];
}

@end
