//
//  Account+Playlists.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account.h"

typedef void (^URLsResultsBlock)(NSArray *urls, NSError *error);

@interface Account (Playlists)
-(void)playlistsForProject:(Project *)project resultsBlock:(PlaylistsResultsBlock)resultsBlock;

-(void)playlistForProject:(Project *)project resultsBlock:(PlaylistsResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock;
-(void)addVideoToPlaylist:(Playlist *)playlist;
-(void)createPlaylist:(Playlist *)playlist project:(Project *)project resultsBlock:(CreateResultsBlock)resultsBlock;
-(void)updatePlaylist:(Playlist *)playlist resultsBlock:(UpdateResultsBlock)resultsBlock;
-(void)deletePlaylist:(Playlist *)playlist resultsBlock:(DeleteResultsBlock)resultsBlock;
-(void)deletePlaylistLameWay:(Playlist *)playlist resultsBlock:(DeleteResultsBlock)resultsBlock;
-(void)playlistUrls:(Playlist *)playlist resultsBlock:(URLsResultsBlock)resultsBlock;
@end
