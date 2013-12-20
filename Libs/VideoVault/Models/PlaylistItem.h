//
//  PlaylistItem.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>

@class SourceVideo;

@interface PlaylistItem : NSObject {
	NSString *playlistItemId, *playlistId, *videoId, *videoName, *createdDate;
	NSURL *thumbnailUrl;
	@public
	int orderIndex;
	double duration;
    int numComments;
}
@property(nonatomic, retain) NSString *playlistItemId, *playlistId, *videoId, *videoName, *createdDate;
@property(nonatomic, retain) NSURL *thumbnailUrl;
@property(nonatomic, readonly) SourceVideo *video;

-(id)initWithVideo:(SourceVideo *)video;
-(NSString *)JSONString;
@end
