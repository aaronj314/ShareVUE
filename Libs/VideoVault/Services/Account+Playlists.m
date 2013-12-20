//
//  Account+Playlists.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account+Playlists.h"
#import "api.h"
#import "JSON.h"
#import "ASIHTTPRequest.h"
#import "ASIFormDataRequest.h"


@implementation Account (Playlists)
-(NSString *)localFormatedDate:(NSDate *)date {
    //NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    //dateFormatter setTimeZone:[NSTimeZone timeZoneForSecondsFromGMT:0]];
    //[dateFormatter setLocale:[[[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"] autorelease]];
    //[dateFormatter setDateFormat:@"yyyy/MM/dd HH:mm:ss"];
    
    NSDateFormatter *dateFormatter2 = [[NSDateFormatter alloc] init];
    [dateFormatter2 setTimeZone:[NSTimeZone localTimeZone]];
    [dateFormatter2 setLocale:[[[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"] autorelease]];
    [dateFormatter2 setDateFormat:@"yyyy/MM/dd"];
    
    //NSDate *noteDate = [dateFormatter dateFromString:d];
    NSString *localDate = [dateFormatter2 stringFromDate:date];
    
    //[dateFormatter release];
    [dateFormatter2 release];
    return localDate;
}



-(void)playlistForProject:(Project *)project resultsBlock:(PlaylistsResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@projects/%@/playlists/", _BACKEND_HOST,project.projectId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setStartedBlock:startedBlock];
    SMLOG(@">>>>PLAYLIST FOR PROJECT REQUEST=%@", url);
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		SMLOG(@"<<<<PLAYLIST FOR PROJECT RESPONSE=%@", jsonString);
		
		NSArray *results = [jsonString JSONValue];
		
		NSMutableArray *playlists = [NSMutableArray arrayWithCapacity:0];
		for (NSDictionary *playlist in results) {
			Playlist *p = [[[Playlist alloc] init] autorelease];
            
            if ([playlist objectForKey:@"CreatedDate"]) {
                NSDate *udate = [NSDate dateWithTimeIntervalSince1970:[[playlist objectForKey:@"CreatedDate"] intValue]];
                p.createdDate = [self localFormatedDate:udate];
             }
			p.playlistId = [[playlist objectForKey:@"Id"] stringValue];
			p.projectId = [[playlist objectForKey:@"ProjectId"] stringValue];
			p.name = [playlist objectForKey:@"Name"];
			p.userId = [[playlist objectForKey:@"UserId"] stringValue];
			p->sharing = [[playlist objectForKey:@"IsPublic"] boolValue];
			p->duration = [[playlist objectForKey:@"Duration"] doubleValue];
            id pli = [playlist objectForKey:@"PlaylistItems"];
			NSArray *playlistItems = pli==[NSNull null] ? nil: pli;
            
            
            
			for (NSDictionary *playlistItem in playlistItems) {
                //NSLog(@"PlaylistItem JSON=%@", playlistItem);
				PlaylistItem *pi = [[PlaylistItem alloc] init];
                if ([playlistItem objectForKey:@"SourceVideoCreated"]) {
                    NSDate *udate = [NSDate dateWithTimeIntervalSince1970:[[playlistItem objectForKey:@"SourceVideoCreated"] intValue]];
                    pi.createdDate = [self localFormatedDate:udate];
                }

                
				pi.playlistItemId = [[playlistItem objectForKey:@"Id"] stringValue];
				pi.playlistId = [[playlistItem objectForKey:@"PlaylistId"] stringValue];
				pi.videoId = [[playlistItem objectForKey:@"SourceVideoId"] stringValue];
				pi->orderIndex = [[playlistItem objectForKey:@"OrderIndex"] intValue];
				pi->duration = [[playlistItem objectForKey:@"Duration"] doubleValue];
                
                NSArray *notes = [playlistItem objectForKey:@"Notes"];
                pi->numComments = [notes count];
				
				id thumbnail = [playlistItem objectForKey:@"ThumbnailUrl"];
                if (![thumbnail isKindOfClass:[NSNull class]]) {
                    pi.thumbnailUrl = [NSURL URLWithString:[playlistItem objectForKey:@"ThumbnailUrl"]];
                }
                //pi.thumbnailUrl = [NSURL URLWithString:[playlistItem objectForKey:@"ThumbnailUrl"]];
				//pi.thumbnailUrl = [NSURL URLWithString:thumbnail];
				
				id vn = [playlistItem objectForKey:@"VideoName"];
				pi.videoName = vn==[NSNull null] ? @"": vn;
				
				//sv.name = [video objectForKey:@"VideoName"];
				//[self getVideo:sv resultsBlock:nil];
				
				[p.playlistItems addObject:pi];
				[pi release];
				//[sv release];
			}
			
			[playlists addObject:p];
		}
		resultsBlock(playlists, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)playlistUrls:(Playlist *)playlist resultsBlock:(URLsResultsBlock)resultsBlock {
    NSMutableArray *tmpArray = [NSMutableArray arrayWithCapacity:[playlist.playlistItems count]];
    for (int i = 0; i < [playlist.playlistItems count]; i++) {
        NSObject *o = [[[NSObject alloc] init] autorelease];
        [tmpArray addObject:o];
    }
    __block int count = 0;
    playlist.playlistUrls = tmpArray;
        for (int i = 0; i < [playlist.playlistItems count]; i++) {
            SourceVideo *v = [playlist.videos objectAtIndex:i];
		//for (SourceVideo *v in playlist.videos) {
            VideoURLResultsBlock blk = ^(NSURL *url, NSError *error){
				NSLog(@"ADDING URL TO PLAYLIST=%@",url);
                [playlist.playlistUrls replaceObjectAtIndex:i withObject:url];
				count++;
				if (count == [playlist.playlistItems count]) {
					dispatch_async(dispatch_get_main_queue(), ^{ resultsBlock(playlist.playlistUrls, nil);});
				}
			} ;
            
            
			[self videoHttpLiveUrl:v resulsBlock:blk];
		}
	
}

-(void)createPlaylist:(Playlist *)playlist project:(Project *)project resultsBlock:(CreateResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@playlists/", _BACKEND_HOST];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request setRequestMethod:@"POST"];
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	
	NSString *plItems = @"\"PlaylistItems\":[";
	int idx = 0;
	for (PlaylistItem *pi in playlist.playlistItems) {
		if (idx == ([playlist.playlistItems count]-1)) {
			plItems = [NSString stringWithFormat:@"%@{\"OrderIndex\":%i, \"SourceVideoId\":%@}", plItems, idx, pi.videoId];
		} else {
			plItems = [NSString stringWithFormat:@"%@{\"OrderIndex\":%i, \"SourceVideoId\":%@},", plItems, idx, pi.videoId];
		}
		idx++;
	}
	plItems = [NSString stringWithFormat:@"%@]", plItems];
	
	NSString *jsonBody = [NSString stringWithFormat:@"{\"ProjectId\":%@,\"IsPublic\":%@,\"Name\":\"%@\",%@}",project.projectId,(playlist->sharing ? @"true" : @"false"), playlist.name, plItems];
	SMLOG(@">>>>CREATE PLAYLIST REQUEST JSON BODY=%@", jsonBody);
	//NSString *jsonBody = [NSString stringWithFormat:@"{\"PlaylistItems\":[{\"SourceVideoId\":\"17\",\"OrderIndex\":0},{\"SourceVideoId\":\"18\",\"OrderIndex\":1}],\"IsPublic\":false,\"Name\":\"android pl\"}} "];
	[request setPostBody:[[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy]];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		SMLOG(@"<<<<CREATE PLAYLIST RESPONSE=%@", jsonString);
		NSDictionary *json = [jsonString JSONValue]; 
		//Playlist *playlist = [[[Playlist alloc] init] autorelease];
		playlist.playlistId = [json valueForKey:@"Id"];
        
        playlist->duration = [[json objectForKey:@"Duration"] doubleValue];
        
        if ([json objectForKey:@"CreatedDate"]) {
            NSDate *udate = [NSDate dateWithTimeIntervalSince1970:[[json objectForKey:@"CreatedDate"] intValue]];
            playlist.createdDate = [self localFormatedDate:udate];
        }
        
		id pli = [json objectForKey:@"PlaylistItems"];
        NSArray *playlistItems = pli==[NSNull null] ? nil: pli;
        
        
        
        for (int i = 0; i < [playlistItems count]; i++) {
            NSDictionary *playlistItem = [playlistItems objectAtIndex:i];
            PlaylistItem *pi = [playlist.playlistItems objectAtIndex:i];
            
            if ([playlistItem objectForKey:@"SourceVideoCreated"]) {
                NSDate *udate = [NSDate dateWithTimeIntervalSince1970:[[playlistItem objectForKey:@"SourceVideoCreated"] intValue]];
                pi.createdDate = [self localFormatedDate:udate];
            }
            
            
            pi.playlistItemId = [[playlistItem objectForKey:@"Id"] stringValue];
            pi.playlistId = [[playlistItem objectForKey:@"PlaylistId"] stringValue];
            //pi.videoId = [[playlistItem objectForKey:@"SourceVideoId"] stringValue];
            //pi->orderIndex = [[playlistItem objectForKey:@"OrderIndex"] intValue];
            pi->duration = [[playlistItem objectForKey:@"Duration"] doubleValue];
            
            NSArray *notes = [playlistItem objectForKey:@"Notes"];
            pi->numComments = [notes count];
            
            id thumbnail = [playlistItem objectForKey:@"ThumbnailUrl"];
            if (![thumbnail isKindOfClass:[NSNull class]]) {
                pi.thumbnailUrl = [NSURL URLWithString:[playlistItem objectForKey:@"ThumbnailUrl"]];
            }
            //pi.thumbnailUrl = [NSURL URLWithString:[playlistItem objectForKey:@"ThumbnailUrl"]];
            //pi.thumbnailUrl = [NSURL URLWithString:thumbnail];
            
            id vn = [playlistItem objectForKey:@"VideoName"];
            pi.videoName = vn==[NSNull null] ? @"": vn;
            
        }
        
        
        
		if (resultsBlock) {
			resultsBlock(playlist, nil);
		}
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

/*
-(void)deletePlaylistLameWay:(Playlist *)playlist resultsBlock:(DeleteResultsBlock)resultsBlock {
    NSString *itemAPI = [NSString stringWithFormat:@"%@playlists/item/", _BACKEND_HOST];
    NSURL *urlItem = [NSURL URLWithString:itemAPI];
    
    
    for (PlaylistItem *item in playlist.playlistItems) {
    __block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:urlItem];
	
	
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	NSString *jsonBody = [NSString stringWithFormat:@"{\"SourceVideoId\": %@, \"PlaylistId\": %@}",item.videoId, item.playlistItemId];
	[request setPostBody:[[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy]];
	//NSLog(@"DELETE PLAYLIST ITMES BODY=%@",jsonBody);
	[request buildPostBody];
	[request setRequestMethod:@"DELETE"];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setDelegate:self];
	METHOD_FUNC_LOG;
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"DELETE PLAYLIST ITEM RESPONSE=%@", jsonString);
        //if (resultsBlock) {
		//	resultsBlock(playlist, nil);
		//}
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
    }
    
    [self deletePlaylist:playlist resultsBlock:resultsBlock];
}
*/

-(void)deletePlaylist:(Playlist *)playlist resultsBlock:(DeleteResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@playlists/%@/", _BACKEND_HOST, playlist.playlistId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	//,\"Name\":\"%@\"
	NSString *jsonBody = [NSString stringWithFormat:@"{\"Id\":%@}", playlist.playlistId];
	//[request setPostBody:[[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy]];
	SMLOG(@"DELETE PLAYLIST REQUEST BODY=%@",jsonBody);
	//[request buildPostBody];
	[request setRequestMethod:@"DELETE"];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setDelegate:self];
	METHOD_FUNC_LOG;
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		SMLOG(@"DELETE PLAYLIST RESPONSE=%@", jsonString);
		if (resultsBlock) {
			resultsBlock(playlist, nil);
		}
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}
/*
-(void)updatePlaylist:(Playlist *)playlist resultsBlock:(UpdateResultsBlock)resultsBlock {
	Project *proj = [[[Project alloc] init] autorelease];
	proj.projectId = playlist.projectId;
	[self deletePlaylist:playlist resultsBlock:nil];
	
	CreateResultsBlock blk = ^(id playlist, NSError *error) {
		resultsBlock(playlist, error);
	};
	[self createPlaylist:playlist project:proj resultsBlock:blk];
}
*/

-(void)updatePlaylist:(Playlist *)playlist resultsBlock:(UpdateResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@playlists/", _BACKEND_HOST];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIFormDataRequest *request = [ASIFormDataRequest requestWithURL:url];
	
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	
	NSString *plItems = @"\"PlaylistItems\":[";
	int idx = 0;
	for (PlaylistItem *pi in playlist.playlistItems) {
		if (idx == ([playlist.playlistItems count]-1)) {
			plItems = [NSString stringWithFormat:@"%@{\"OrderIndex\":%i, \"SourceVideoId\":%@}", plItems, idx, pi.videoId];
		} else {
			plItems = [NSString stringWithFormat:@"%@{\"OrderIndex\":%i, \"SourceVideoId\":%@},", plItems, idx, pi.videoId];
		}
		idx++;
	}
	plItems = [NSString stringWithFormat:@"%@]", plItems];
	
	NSString *jsonBody = [NSString stringWithFormat:@"{\"Id\":%@,\"Name\":\"%@\",\"ProjectId\":%@, \"UserId\":%@, %@}", playlist.playlistId, playlist.name, playlist.projectId, playlist.userId, plItems];
	
	//NSLog(@"UPDATE PLAYLIST BODY=%@", jsonBody);
	[request setPostBody:[[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy]];
	[request buildPostBody];
	[request setRequestMethod:@"PUT"];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"RESPONSE=%@", jsonString);
		//NSDictionary *json = [jsonString JSONValue]; 
		//Playlist *playlist = [[[Playlist alloc] init] autorelease];
		//playlist.playlistId = [json valueForKey:@"Id"];
		//playlist.name = [json valueForKey:@"Name"];
		resultsBlock(playlist, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}
@end
