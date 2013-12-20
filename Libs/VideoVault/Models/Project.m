//
//  Project.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Project.h"
#import "SourceVideo.h"
#import "Asset.h"
#import "Playlist.h"


@implementation Project
@synthesize projectId, name, description, videoCount, playlistCount, documentCount;
@synthesize videos, assets, playlists;

+(NSMutableArray *)projectsForUser:(NSString *)username {
	return [NSMutableArray arrayWithArray:[self projectsForDemo]];
}
			
			
+(NSMutableArray *)projectsForDemo {
	Project *p1 = [[[Project alloc] init] autorelease];
	p1.name = @"Demo 1";
	p1.description = @"Demo 1 project description goes here";
	
	Project *p2 = [[[Project alloc] init] autorelease];
	p2.name = @"Demo 2";
	p2.description = @"Demo 2 project description goes here";
	
	//add videos
	p1.videos = [SourceVideo videosForDemo:1];
	p2.videos = [SourceVideo videosForDemo:8];
	
	
	//add playlist
	p1.playlists = [Playlist playlistsForDemo];
	p2.playlists = [Playlist playlistsForDemo];
	
	// add asset
	p1.assets = [Asset assetsForDemo];
	p2.assets = [Asset assetsForDemo];
	return [NSMutableArray arrayWithObjects:p1, p2, nil];
	
}

- (void) dealloc{
	//NSLog(@"dealloc::%@", [self class]);
	[projectId release];
	[name release];
	[description release];
	[videos release];
	[assets release];
	[playlists release];
	[super dealloc];
}

@end
