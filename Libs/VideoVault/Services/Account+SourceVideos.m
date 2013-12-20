//
//  Account_Video.m
//  TechnicolorDailies
//
//  fd by Aaron Jones on 1/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account+SourceVideos.h"
#import "api.h"
#import "JSON.h"
#import "ASIHTTPRequest.h"
#import "ASIFormDataRequest.h"
#import "Reachability.h"

//http://dev-videovault.sorensonmedia.com/vapi/projects/{PROJECTID}/videos/

@implementation Account (SourceVideo)
-(void)getVideo:(SourceVideo *)video resultsBlock:(GetResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@sourcevideos/%@/", _BACKEND_HOST,video.videoId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        //NSLog(@"GET VIDEO (ID=%@) RESPONSE=%@", video.videoId, jsonString);
		
		NSDictionary *json = [jsonString JSONValue];
		video.name = [json objectForKey:@"Name"];
		video.fileName = [json	objectForKey:@"FileName"];
		video.thumbnailUrl = [NSURL URLWithString:[json objectForKey:@"ThumbnailUrl"]];
		
		if (resultsBlock) {
			resultsBlock(video, nil);
		}
		[jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		if (resultsBlock) {
			resultsBlock(nil, error);
		}
		
	}];
	
	[request startAsynchronous];
}

-(void)getVideoALE:(SourceVideo *)video resultsBlock:(GetResultsBlock)resultsBlock {
    NSString *prjAPI = [NSString stringWithFormat:@"%@sourcevideos/%@/", _BACKEND_HOST,video.videoId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
        //NSLog(@"GET ALE VIDEO DATA (ID=%@)", video.videoId);
		
		NSDictionary *json = [jsonString JSONValue];
        video.metadata = [NSMutableArray arrayWithCapacity:0];
        
        NSArray *ales = [json objectForKey:@"AleList"];
        
        if ((id)ales != [NSNull null]) {
            for (NSDictionary *ale in ales) {
                SMetadata *md = [[SMetadata alloc] init];
                md.metadataId = [ale objectForKey:@"Id"];
                md.name = [ale objectForKey:@"Name"];
                md.value = [ale objectForKey:@"Value"];
                [video.metadata addObject:md];
            }
        }
        
		//NSLog(@"ALE VIDEO DATA (%@)", video.metadata);
        
		if (resultsBlock) {
			resultsBlock(video, nil);
		}
		[jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		if (resultsBlock) {
			resultsBlock(nil, error);
		}
		
	}];
	
	[request startAsynchronous];
}

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

#pragma mark -
#pragma get all videos
/************* THIS ONE IS USED ****************/
-(void)videosForProject:(Project *)project resultsBlock:(VideosResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock{
	NSString *prjAPI = [NSString stringWithFormat:@"%@projects/%@/sourcevideos/?offset=0&limit=%@", _BACKEND_HOST, project.projectId, project.videoCount];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setStartedBlock:startedBlock];
    
    SMLOG(@">>>>Source Videos FOR PROJECT REQUEST=%@", url);
    
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		SMLOG(@"<<<<VIDEOS FOR PROJECT RESPONSE=%@", jsonString);
		
		NSArray *results = [[jsonString JSONValue] objectForKey:@"Entities"];
		
		NSMutableArray *videos = [NSMutableArray arrayWithCapacity:0];
		for (NSDictionary *video in results) {
			SourceVideo *v = [[[SourceVideo alloc] init] autorelease];
            v.metadata = [NSMutableArray arrayWithCapacity:0];
            
            NSArray *ales = [video objectForKey:@"AleList"];
            
            if ((id)ales != [NSNull null]) {
            for (NSDictionary *ale in ales) {
                SMetadata *md = [[[SMetadata alloc] init] autorelease];
                md.metadataId = [ale objectForKey:@"Id"];
                md.name = [ale objectForKey:@"Name"];
                md.value = [ale objectForKey:@"Value"];
                [v.metadata addObject:md];
            }
            }

            if ([video objectForKey:@"Created"]) {
                NSDate *udate = [NSDate dateWithTimeIntervalSince1970:[[video objectForKey:@"Created"] intValue]];
                v.createdDate = [self localFormatedDate:udate];
            }
            
            
			v.videoId = [[video objectForKey:@"Id"] stringValue];
			v.projectId = [[video objectForKey:@"ProjectId"] stringValue];
			v.name = [video objectForKey:@"Name"];
			v.fileName = [video objectForKey:@"FileName"];
			v->commentCount = [[video objectForKey:@"CommentCount"] intValue];
			v->duration = [[video objectForKey:@"Duration"] doubleValue];
			//v.thumbnailUrl = [NSURL URLWithString:[video objectForKey:@"ThumbnailUrl"]];
			id t = [video objectForKey:@"ThumbnailUrl"];
			v.thumbnailUrl = (t==[NSNull null] ? nil : [NSURL URLWithString:t]);
			
			[videos addObject:v];
			
		}
		resultsBlock(videos, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)videosForProject:(Project *)project resultsBlock:(VideosResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock aleKey:(NSString *)key aleValue:(NSString *)value {
    NSString *prjAPI = [NSString stringWithFormat:@"%@projects/%@/sourcevideos/?offset=0&limit=%@&ale_name=%@&ale_value=%@", _BACKEND_HOST, project.projectId, project.videoCount, key, value];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
    
    SMLOG(@">>>>Source Videos FOR PROJECT REQUEST=%@", url);
    
	[request setStartedBlock:startedBlock];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		SMLOG(@"<<<<VIDEOS FOR PROJECT RESPONSE=%@", jsonString);
		
		NSArray *results = [[jsonString JSONValue] objectForKey:@"Entities"];
		
		NSMutableArray *videos = [NSMutableArray arrayWithCapacity:0];
		for (NSDictionary *video in results) {
			SourceVideo *v = [[[SourceVideo alloc] init] autorelease];
            v.metadata = [NSMutableArray arrayWithCapacity:0];
            
            NSArray *ales = [video objectForKey:@"AleList"];
            
            if ((id)ales != [NSNull null]) {
                for (NSDictionary *ale in ales) {
                    SMetadata *md = [[SMetadata alloc] init];
                    md.metadataId = [ale objectForKey:@"Id"];
                    md.name = [ale objectForKey:@"Name"];
                    md.value = [ale objectForKey:@"Value"];
                    [v.metadata addObject:md];
                }
            }
            
            
			v.videoId = [[video objectForKey:@"Id"] stringValue];
			v.projectId = [[video objectForKey:@"ProjectId"] stringValue];
			v.name = [video objectForKey:@"Name"];
			v.fileName = [video objectForKey:@"FileName"];
			v->commentCount = [[video objectForKey:@"CommentCount"] intValue];
			v->duration = [[video objectForKey:@"Duration"] doubleValue];
			//v.thumbnailUrl = [NSURL URLWithString:[video objectForKey:@"ThumbnailUrl"]];
			id t = [video objectForKey:@"ThumbnailUrl"];
			v.thumbnailUrl = (t==[NSNull null] ? nil : [NSURL URLWithString:t]);
			
			[videos addObject:v];
			
		}
		resultsBlock(videos, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)videoUrl:(SourceVideo *)video preset:(NSString *)preset resulsBlock:(VideoURLResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@sourcevideos/%@/urllist/", _BACKEND_HOST, video.videoId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"VIDEO URL RESPONSE=%@", jsonString);
		
		NSArray *results = [jsonString JSONValue];
		
		NSURL *url = nil;
		for (NSDictionary *video in results) {
			//NSLog(@"PresetName=%@", [video objectForKey:@"PresetName"]);
			NSString *preset = [video objectForKey:@"PresetName"];
			if ([preset isEqualToString:@"Apple Adaptive Http Live"]) {
				//NSLog(@"FOUND \"Apple Adaptive Http Live\"" );
				url = [NSURL URLWithString:[video objectForKey:@"Url"]];
				break;
			} else if ([preset isEqualToString:@"MPEG4-AVC-720p"]) {
				url = [NSURL URLWithString:[video objectForKey:@"Url"]];
			}

		}
		// for testing do NOT remove, or the Live HTTP streaming gods will curse you!!!
		//url = [NSURL URLWithString:@"http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8"];
		
		resultsBlock(url, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(BOOL)isWiFiEnabled {
    Reachability *r = [Reachability reachabilityForLocalWiFi];
    NetworkStatus internetStatus = [r currentReachabilityStatus];
    if (internetStatus == ReachableViaWiFi) {
        return YES;
    } else if (internetStatus == ReachableViaWWAN) {
        return NO;
    } else {
        return NO;
    }
}

#pragma mark -
#pragma get HTTP Live streaming URL
-(void)videoHttpLiveUrl:(SourceVideo *)video resulsBlock:(VideoURLResultsBlock)resultsBlock {
    NSString *prjAPI = [NSString stringWithFormat:@"%@sourcevideos/%@/urllist/", _BACKEND_HOST, video.videoId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
    SMLOG(@">>>>HTTP LIVE VIDEO URL REQUEST=%@", url);
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		SMLOG(@"<<<<HTTP LIVE VIDEO URL RESPONSE=%@", jsonString);
        
        NSString *presetType = nil;
        BOOL wifi = NO;
        
        if ([self isWiFiEnabled]) {
            presetType = @"Apple Adaptive Higher";
            wifi = YES;
        } else {
            presetType = @"Apple Adaptive";
        }
		
		NSArray *results = [jsonString JSONValue];
		
		NSURL *url = nil;
        NSMutableDictionary *urlList = [NSMutableDictionary dictionary];
        
		for (NSDictionary *video in results) {
			//NSLog(@"PresetName=%@", [video objectForKey:@"PresetName"]);
			NSString *preset = [video objectForKey:@"PresetName"];
			if ([preset isEqualToString:@"Apple Adaptive Higher"] || [preset isEqualToString:@"Apple Adaptive"]) {
                url = [NSURL URLWithString:[video objectForKey:@"Url"]];
                [urlList setObject:url forKey:preset];
				//NSLog(@"FOUND PresetName==\"%@\"", presetType);
            //    
            //    if (wifi && [preset isEqualToString:presetType]) {
            //        break;
            //    }
				
			}            
		}
        
        if (wifi && [urlList objectForKey:@"Apple Adaptive Higher"]) {
            url = [urlList objectForKey:@"Apple Adaptive Higher"];
        } else if (wifi && [urlList objectForKey:@"Apple Adaptive"]) {
            url = [urlList objectForKey:@"Apple Adaptive"]; 
        } else if (!wifi && [urlList objectForKey:@"Apple Adaptive"]) {
             url = [urlList objectForKey:@"Apple Adaptive"];
        }
        
		// for testing do NOT remove, or the Live HTTP streaming gods will curse you!!!
        if (url == nil) {
            url = [NSURL URLWithString:@"http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8"];
        }
		
        //url = [NSURL URLWithString:@"http://192.168.1.100/~aaron/stream/prog_index.m3u8"];
		resultsBlock(url, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

/*
-(void)videoHttpLiveUrl:(SourceVideo *)video resulsBlock:(VideoURLResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@sourcevideos/%@/httplive/", _BACKEND_HOST, video.videoId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	NSLog(@"HTTP LIVE VIDEO URL REQUEST=%@", url);
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		NSLog(@"HTTP LIVE VIDEO URL RESPONSE=%@", jsonString);
		
		NSDictionary *video = [jsonString JSONValue];
        
        [self isWiFiEnabled];
		
		NSURL *url = nil;
		NSLog(@"PresetName=%@", [video objectForKey:@"PresetName"]);
        url = [NSURL URLWithString:[video objectForKey:@"Url"]];
       
        //NSString *nonSSL = [[video objectForKey:@"Url"] stringByReplacingOccurrencesOfString:@"https://" withString:@"http://"];
        //NSLog(@"Live Stream URL=%@", nonSSL);
		//url = [NSURL URLWithString:nonSSL];
        //url = [NSURL URLWithString:@"http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8"];
        //url = [NSURL URLWithString:@"http://50.18.44.254/sita_sings.m3u8"];
        //url = [NSURL URLWithString:@"http://d1n5b38jzw8irs.cloudfront.net/cod.mp4"];
        //url = [NSURL URLWithString:@"http://ios-enc-test.s3.amazonaws.com/dd/doubledragon.m3u8"];
        
		resultsBlock(url, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}
*/
-(void)videosUrls:(SourceVideo *)video resultsBlock:(VideoURLsResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@sourcevideos/%@/urllist/", _BACKEND_HOST, video.videoId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		NSLog(@"VIDEO URLS RESPONSE=%@", jsonString);
		
		NSArray *results = [jsonString JSONValue];
		
		NSMutableArray *urls = [NSMutableArray arrayWithCapacity:0];
		for (NSDictionary *video in results) {
			//SourceVideo *v = [[[SourceVideo alloc] init] autorelease];
			//v.videoId = [video objectForKey:@"Id"];
			//v.presetId = [video objectForKey:@"PresetId"];
			//v.presetName = [video objectForKey:@"PresetName"];
			//NSString *http = [[video objectForKey:@"Url"] stringByReplacingOccurrencesOfString:@"https" withString:@"http"];
			NSURL *url = [NSURL URLWithString:[video objectForKey:@"Url"]];
			
			[urls addObject:url];
		}
		resultsBlock(urls, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}
@end
