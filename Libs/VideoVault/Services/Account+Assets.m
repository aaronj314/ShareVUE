//
//  Account+Assets.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account+Assets.h"
#import "api.h"
#import "JSON.h"
#import "ASIHTTPRequest.h"
#import "ASIFormDataRequest.h"


@implementation Account (Assets)
-(void)assetsForProject:(Project *)project resultsBlock:(AssetsResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@projects/%@/documents/?offset=0&limit=%@", _BACKEND_HOST, project.projectId, project.videoCount];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"RESPONSE=%@", jsonString);
		NSArray *json = [[jsonString JSONValue] objectForKey:@"Entities"];
		
		NSMutableArray *assets = [NSMutableArray arrayWithCapacity:0];
		for (NSDictionary *project in json) {
			Asset *a = [[[Asset alloc] init] autorelease];
			a.assetId = [[project objectForKey:@"Id"] stringValue];
			a.name = [project objectForKey:@"Name"];
			a.projectId = [[project objectForKey:@"ProjectId"] stringValue];
			a.url = [NSURL URLWithString:[project objectForKey:@"Url"]];
			[assets addObject:a];
		}
		resultsBlock(assets, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)accountAssets:(AssetsResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@%@%", _BACKEND_HOST, @"documents/"];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request setRequestMethod:@"GET"];
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"RESPONSE=%@", jsonString);
		NSArray *json = [jsonString JSONValue];
		
		NSMutableArray *assets = [NSMutableArray arrayWithCapacity:0];
		for (NSDictionary *project in json) {
			Asset *a = [[[Asset alloc] init] autorelease];
			a.assetId = [[project objectForKey:@"Id"] stringValue];
			a.name = [project objectForKey:@"Name"];
			a.projectId = [[project objectForKey:@"ProjectId"] stringValue];
			a.url = [NSURL URLWithString:[project objectForKey:@"Url"]];
			[assets addObject:a];
		}
		resultsBlock(assets, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)createAssetWithName:(NSString *)name resultsBlock:(CreateResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@%@%", _BACKEND_HOST, @"documents/"];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request setRequestMethod:@"POST"];
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	
	NSString *jsonBody = [NSString stringWithFormat:@"{\"Name\":\"Test Doc\",\"ProjectId\":1,\"Url\":\"http://nowhere.com\"}", name];
	[request setPostBody:[[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy]];
	
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"RESPONSE=%@", jsonString);
		
		resultsBlock(nil, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)updateAsset:(Asset *)asset resultsBlock:(UpdateResultsBlock)resultsBlock {}
-(void)deleteAsset:(Asset *)asset resultsBlock:(DeleteResultsBlock)resultsBlock {}
@end
