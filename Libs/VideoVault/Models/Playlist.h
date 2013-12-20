//
//  Playlist.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SourceVideo;
@class PlaylistItem;

@interface Playlist : NSObject {
	NSString *playlistId, *name, *userId, *projectId, *createdDate;
	NSMutableArray *playlistItems;
    NSMutableArray *playlistUrls;
	
	@public
	BOOL sharing;
    double duration;
}
@property (nonatomic, retain) NSString *playlistId, *name, *userId, *projectId, *createdDate;
@property (nonatomic, retain) NSMutableArray *playlistItems;
@property (nonatomic, retain) NSMutableArray *playlistUrls;
@property (readonly) NSMutableArray *videos;
@property (readonly) NSURL *thumbnailUrl;

-(void)addPlaylistItemsFromVideos:(NSMutableArray *)videos;
-(NSString *)JSONString;

//demo code
+(NSMutableArray *)playlistsForDemo;
@end
