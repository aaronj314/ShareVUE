//
//  Account+Comments.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account+Comments.h"
#import "api.h"
#import "JSON.h"
#import "ASIHTTPRequest.h"
#import "ASIFormDataRequest.h"

@implementation Account (Comments)

-(NSString *)localFormatedDate:(NSString *)d {
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc] init];
    [dateFormatter setTimeZone:[NSTimeZone timeZoneForSecondsFromGMT:0]];
    [dateFormatter setLocale:[[[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"] autorelease]];
    [dateFormatter setDateFormat:@"yyyy/MM/dd HH:mm:ss"];
    
    NSDateFormatter *dateFormatter2 = [[NSDateFormatter alloc] init];
    [dateFormatter2 setTimeZone:[NSTimeZone localTimeZone]];
    [dateFormatter2 setLocale:[[[NSLocale alloc] initWithLocaleIdentifier:@"en_US_POSIX"] autorelease]];
    [dateFormatter2 setDateFormat:@"yyyy/MM/dd HH:mm:ss"];
    
    NSDate *noteDate = [dateFormatter dateFromString:d];
    NSString *localDate = [dateFormatter2 stringFromDate:noteDate];
    
    [dateFormatter release];
    [dateFormatter2 release];
    return localDate;
}

-(void)commentsForVideo:(SourceVideo *)video resultsBlock:(CommentsResultsBlock)resultsBlock {
    // NSTimeZone *lo = [NSTimeZone localTimeZone];
    //"2011\/05\/25 21:05:27"
	NSString *prjAPI = [NSString stringWithFormat:@"%@sourcevideos/%@/notes/", _BACKEND_HOST, video.videoId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"COMMENTS FOR VIDEO RESPONSE=%@", jsonString);
		
		NSArray *results = [jsonString JSONValue];
		
		NSMutableArray *comments = [NSMutableArray arrayWithCapacity:0];
        
		for (NSDictionary *comment in results) {
			Comment *c = [[[Comment alloc]  init] autorelease];
			c.value = [comment objectForKey:@"Comment"];
			c.created = [self localFormatedDate:[comment objectForKey:@"NoteDate"]];
            
			c.commentId = [[comment objectForKey:@"Id"] stringValue];
			c.timecode = [[comment objectForKey:@"Timecode"] doubleValue];
			c.userId = [[comment objectForKey:@"UserId"] stringValue];
            c.userName = [comment objectForKey:@"UserName"];
			[comments addObject:c];
		}
        
        NSArray *sortedArray = [comments sortedArrayUsingComparator: ^(id obj1, id obj2) {
            Comment *c1 = (Comment *)obj1;
            Comment *c2 = (Comment *)obj2;
            
            if (c1.timecode > c2.timecode) {
                return (NSComparisonResult)NSOrderedDescending;
            }
            
            if (c1.timecode < c2.timecode) {
                return (NSComparisonResult)NSOrderedAscending;
            }
            return (NSComparisonResult)NSOrderedSame;
        }];
        
        NSMutableArray *mArray = [sortedArray mutableCopy];
		video.comments = mArray ;
		resultsBlock(mArray, nil);
        [jsonString release];
        [mArray release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)createComment:(Comment *)comment video:(SourceVideo *)video userId:(NSString *)userId resultsBlock:(CreateResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@notes/", _BACKEND_HOST];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request setRequestMethod:@"POST"];
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	NSString *jsonBody = [NSString stringWithFormat:@"{\"Comment\":\"%@\",\"SourceVideoId\":%@,\"Timecode\":%f,\"UserId\":%@}", comment.value, video.videoId, comment.timecode, userId ];
	//NSLog(@"CREATE COMMENT FOR VIDEO REQUEST BODY=%@", jsonBody);
    NSMutableData *postBody = [[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy];
	[request setPostBody:postBody];
    [postBody release];
	
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"CREATE COMMENT FOR VIDEO RESPONSE=%@", jsonString);
		NSDictionary *json = [jsonString JSONValue]; 
		comment.commentId = [[json objectForKey:@"Id"] stringValue];
        //comment.created = [json objectForKey:@"NoteDate"];
        comment.created = [self localFormatedDate:[json objectForKey:@"NoteDate"]];
        comment.userName = [json objectForKey:@"UserName"];
		resultsBlock(comment, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
        //NSLog(@"CREATE COMMENT FOR VIDEO ERROR=%@", error);
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)deleteComment:(Comment *)comment resultsBlock:(DeleteResultsBlock)resultsBlock {
    NSString *prjAPI = [NSString stringWithFormat:@"%@notes/%@/", _BACKEND_HOST, comment.commentId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	//NSString *jsonBody = [NSString stringWithFormat:@"{\"Id\":%@}", comment.commentId ];
	//[request setPostBody:[[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy]];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setRequestMethod:@"DELETE"];
	[request setDelegate:self];
	//NSLog(@"DELETE COMMENT FOR VIDEO REQUEST=%@", prjAPI);
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"DELETE COMMENT FOR VIDEO RESPONSE=%@", jsonString);
		//NSDictionary *json = [jsonString JSONValue]; 
		//comment.commentId = [[json objectForKey:@"Id"] stringValue];
		
        if (resultsBlock) {
            resultsBlock(comment, nil);
        }
        
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
         if (resultsBlock) {
			 //NSLog(@"DELETE COMMENT FOR VIDEO ERROR=%@", error);
             resultsBlock(nil, error);
         }
	}];
	
	[request startAsynchronous];
    [comment release];
}

@end
