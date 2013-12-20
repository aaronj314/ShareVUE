//
//  Video.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "SourceVideo.h"
#import "Project.h"
#import "Comment.h"

@implementation SourceVideo
@synthesize videoId, projectId, name, fileName, createdDate;
@synthesize comments, urls, url, thumbnailUrl;
@synthesize metadata;

+(NSMutableArray *)videosForDemo:(NSInteger)idx {
	NSMutableArray *a = [NSMutableArray arrayWithCapacity:10];
	
	for (int i = 0; i < 7; i++) {
		SourceVideo *v =[[[SourceVideo alloc] init] autorelease];
		v.videoId = @"123456789";
		v.name = [NSString stringWithFormat: @"Sample Clip %i", idx];
		v.url = [SourceVideo localMovieURL:idx];
		++idx;
		v.comments = [Comment commentsForDemo];
		[a addObject:v];
	}
	return a;
}


+(NSURL *)localMovieURL:(NSInteger)i {
	NSURL *u = nil;
	NSBundle *bundle = [NSBundle mainBundle];
	NSString *n = [NSString stringWithFormat:@"demo%i", i];
	
	NSString *moviePath = [bundle pathForResource:n ofType:@"MOV"];
	//NSLog(@"file path=%@", moviePath);	
	if (moviePath) {
		
		u = [NSURL fileURLWithPath:moviePath];
		//NSLog(@"file url=%@", u);
	}
    
    return u;
}

- (void) dealloc
{
	//NSLog(@"dealloc::%@", [self class]);
    [createdDate release];
	[fileName release];
	[videoId release];
	[projectId release];
	[name release];
	[comments release];
    [metadata release];
	[url release];
	[super dealloc];
}
@end
