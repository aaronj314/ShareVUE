//
//  API.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import "Account.h"
#import "Account+Playlists.h"
#import "Account+SourceVideos.h"
#import "Account+Projects.h"
#import "Account+Assets.h"
#import "Account+Comments.h"
#import "User.h"
#import "Project.h"
#import "Playlist.h"
#import "SourceVideo.h"
#import "Comment.h"
#import "Asset.h"
#import "Metadata.h"
#import "PlaylistItem.h"

#define METHOD_LOG (NSLog(@"%@ %s\n%@", \
NSStringFromSelector(_cmd), __FILE__, self))

#define METHOD_FUNC_LOG (NSLog(@"%s", __FUNCTION__))
