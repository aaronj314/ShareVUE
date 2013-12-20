//
//  Playlist.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Playlist.h"
#import "SourceVideo.h"
#import "PlaylistItem.h"

@implementation Playlist
@synthesize playlistId, name, userId, projectId, createdDate;
@synthesize playlistItems;
@synthesize playlistUrls;

-(id)init {
	self = [super init];
	if (self != nil) {
		self.playlistItems = [NSMutableArray arrayWithCapacity:0];
		sharing = NO;
	}
	return self;
}

-(NSMutableArray *)videos {
	NSMutableArray *vids = [NSMutableArray arrayWithCapacity:[playlistItems count]];
	for (PlaylistItem *pi in playlistItems) {
		SourceVideo *sv = [[[SourceVideo alloc] init] autorelease];
		sv.videoId = pi.videoId;
		sv.name = pi.videoName;
		sv.thumbnailUrl = pi.thumbnailUrl;
		[vids addObject:sv];
	}
	return vids;
}

-(NSURL *)thumbnailUrl {
	if ([playlistItems count] > 0) {
		return ((PlaylistItem *)[playlistItems objectAtIndex:0]).thumbnailUrl;
	} else {
		return nil;
	}

}
															  

-(void)addPlaylistItemsFromVideos:(NSMutableArray *)videos {
	int idx = 0;
	for (SourceVideo *sv in videos) {
		PlaylistItem *p = [[PlaylistItem alloc] init];
		p.videoId = sv.videoId;
		p.playlistId = self.playlistId;
		p.videoName = sv.name;
		p.thumbnailUrl = sv.thumbnailUrl;
		p->orderIndex = idx;
		p->duration = sv->duration;
		idx++;
		[self.playlistItems addObject:p];
		[p release];
	}
	//[self.playlistItems addObjectsFromArray:selectedVideos];
}

#pragma mark -
#pragma mark DEMO CODE
+(NSMutableArray *)playlistsForDemo {
	Playlist *p1 = [[[Playlist alloc] init] autorelease];
	p1.name = @"Circled Takes Only";
	//p1.videos = [SourceVideo videosForDemo:1];
	
	Playlist *p2 = [[[Playlist alloc] init] autorelease];
	p2.name = @"VFX Shots";
	//p2.videos = [SourceVideo videosForDemo:1];
	
	Playlist *p3 = [[[Playlist alloc] init] autorelease];
	p3.name = @"Last Takes Only";
	//p3.videos = [SourceVideo videosForDemo:1];
	
	return [NSMutableArray arrayWithObjects:p1, p2, p3, nil];
}

-(NSString *)JSONString {
	/*
	{
		"Created":"\/Date(928149600000+0000)\/",
		"Id":2147483647,
		"IsPublic":true,
		"Name":"String content",
		"PlaylistItems":[{
			"Duration":1.26743233E+15,
			"Id":2147483647,
			"OrderIndex":2147483647,
			"PlaylistId":2147483647,
			"SourceVideoId":2147483647,
			"ThumbnailUrl":"String content",
			"VideoName":"String content"
		}],
		"ProjectId":2147483647,
		"UserId":2147483647
	}*/
	
	NSString *json = [NSString stringWithFormat:@"{\"Created\":\"%@\",\"Id\":\"%@\",\"IsPublic\":%@,\"Name\":\"%@\",\"ProjectId\":%@,\"UserId\":%@"];
	
	
	return json;
}

-(void)dealloc {
	//NSLog(@"dealloc::%@", [self class]);
	[projectId release];
	[playlistId release];
	[name release];
	[userId release];
	[playlistItems release];
    [playlistUrls release];
	[super dealloc];
}

@end
