//
//  Project.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SourceVideo;
@class Asset;
@class Playlist;


@interface Project : NSObject {
	NSString *projectId, *name, *description, *videoCount, *playlistCount, *documentCount;
	NSMutableArray *videos, *assets, *playlists;
}
@property (nonatomic, retain) NSString *projectId, *name, *description, *videoCount, *playlistCount, *documentCount;
@property (nonatomic, retain) NSMutableArray *videos, *assets, *playlists;

+(NSMutableArray *)projectsForUser:(NSString *)username;

+(NSMutableArray *)projectsForDemo;
@end
