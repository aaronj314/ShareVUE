//
//  PlaylistItem.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PlaylistItem.h"
#import "SourceVideo.h"


@implementation PlaylistItem
@synthesize playlistItemId, playlistId, videoId, thumbnailUrl, videoName, createdDate;

-(id)init {
	self = [super init];
	if (self != nil) {
		duration = 0.0;
		orderIndex = 0;
	}
	return self;
}

-(id)initWithVideo:(SourceVideo *)video {
	self = [self init];
	if (self != nil) {
		self.videoId = video.videoId;
		self.thumbnailUrl = video.thumbnailUrl;
		self.videoName = video.name;
	}
	return self;
}

-(SourceVideo *)video {
		SourceVideo *sv = [[[SourceVideo alloc] init] autorelease];
		sv.videoId = videoId;
		sv.name = videoName;
		sv.thumbnailUrl = thumbnailUrl;
	return sv;
}

-(NSString *)JSONString {
	/*
	 "Duration":1.26743233E+15,
	 "Id":2147483647,
	 "OrderIndex":2147483647,
	 "PlaylistId":2147483647,
	 "SourceVideoId":2147483647,
	 "ThumbnailUrl":"String content",
	 "VideoName":"String content"
	 */
	NSString *json = [NSString stringWithFormat:@"{\"Id\":%@,\"Duration\":%@,\"OrderIndex\":%@,\"PlaylistId\":%@,\"SourceVideo\":\"%@\"}"];
	
	return json;
}

-(void)dealloc {
    [createdDate release];
	[videoName release];
	[playlistItemId release];
	[playlistId release];
	[videoId release];
	[thumbnailUrl release];
	[super dealloc];
}

@end
