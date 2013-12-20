//
//  Video.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class Playlist;
@class Comment;
@class Project;


@interface SourceVideo : NSObject {
	NSString *videoId, *projectId, *name, *fileName, *createdDate;
	NSMutableArray *comments, *sources, *metadata;
	NSMutableArray *urls;
	NSURL *url;
	NSURL *thumbnailUrl;
	
	@public
	double duration;
	int commentCount;
}
@property (nonatomic, retain) NSString *videoId, *projectId, *name, *fileName, *createdDate;
@property (nonatomic, retain) NSMutableArray *comments, *urls, *metadata;
@property (nonatomic, retain) NSURL *url, *thumbnailUrl;

//demo code
+(NSMutableArray *)videosForDemo:(NSInteger)idx;
@end
