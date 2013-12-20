//
//  Account+Projects.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account+Projects.h"
#import "api.h"
#import "JSON.h"
#import "ASIHTTPRequest.h"
#import "ASIFormDataRequest.h"

@implementation Account (Projects)
-(void)accountProjects:(ProjectsResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock {
	if (self.user.projects) {
		//NSLog(@"Hitting cache");
		resultsBlock(self.user.projects, nil);
		return;
	}
	
	NSString *prjAPI = [NSString stringWithFormat:@"%@projects/", _BACKEND_HOST];
	NSURL *url = [NSURL URLWithString:prjAPI];
	[ASIHTTPRequest setDefaultTimeOutSeconds:60];
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setStartedBlock:startedBlock];
    //NSLog(@"PROJECT LIST REQUEST=%@", url);
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"PROJECT LIST RESPONSE=%@", jsonString);
		
		NSArray *results = [jsonString JSONValue];
		
		NSMutableArray *projects = [NSMutableArray arrayWithCapacity:0];
		for (NSDictionary *project in results) {
			Project *p = [[[Project alloc] init] autorelease];
			p.projectId = [[project objectForKey:@"Id"] stringValue];
			p.name = [project objectForKey:@"Name"];
			p.videoCount = [[project objectForKey:@"VideoCount"] stringValue];
			p.playlistCount = [[project objectForKey:@"PlaylistCount"] stringValue];
			p.documentCount = [[project objectForKey:@"DocumentCount"] stringValue];
			[projects addObject:p];
		}
		// load array with Videos before call ing result block;
		self.user.projects = projects;
		resultsBlock(projects, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
        //NSLog(@"PROJECT LIST ERROR=%@", error);
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)getProject:(Project *)project resultsBlock:(GetResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@projects/%@/", _BACKEND_HOST, project.projectId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"RESPONSE=%@", jsonString);
		
		NSDictionary *results = [jsonString JSONValue];
			project.projectId = [[results objectForKey:@"Id"] stringValue];
			project.name = [results objectForKey:@"Name"];
			project.videoCount = [[results objectForKey:@"VideoCount"] stringValue];
			project.playlistCount = [[results objectForKey:@"PlaylistCount"] stringValue];
			project.documentCount = [[results objectForKey:@"DocumentCount"] stringValue];
		// load array with Videos before call ing result block;
		resultsBlock(project, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)projectAleKeysForProject:(Project *)project resultsBlock:(GetResultsBlock)resultsBlock {
    NSString *prjAPI = [NSString stringWithFormat:@"%@projects/%@/ale-keys/", _BACKEND_HOST, project.projectId];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		NSLog(@"ALE KEYS FOR PROJECT=%@ RESPONSE=%@",project.name, jsonString);
        NSArray *list = [jsonString JSONValue];
        
        resultsBlock(list, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)projectAleValuesForProject:(Project *)project key:(NSString *)key resultsBlock:(GetResultsBlock)resultsBlock {
    NSString *prjAPI = [NSString stringWithFormat:@"%@projects/%@/ale-values/?ale-key=%@", _BACKEND_HOST, project.projectId, key];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		NSLog(@"ALE VALUES FOR PROJECT=%@, KEY=%@, RESPONSE=%@", project.name, key, jsonString);
		
		NSArray *list = [jsonString JSONValue];
        
        resultsBlock(list, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

-(void)createProject:(Project *)project resultsBlock:(CreateResultsBlock)resultsBlock {
	NSString *prjAPI = [NSString stringWithFormat:@"%@%@%", _BACKEND_HOST, @"projects/"];
	NSURL *url = [NSURL URLWithString:prjAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
	
	[request setRequestMethod:@"POST"];
	[request addRequestHeader:@"Content-Type" value:@"application/json"];
	[request addRequestHeader:X_AUTH_TOKEN value:self.user.token];
	NSString *jsonBody = [NSString stringWithFormat:@"{\"Name\":\"%@\"}", project.name];
	[request setPostBody:[[jsonBody dataUsingEncoding:NSUTF8StringEncoding] mutableCopy]];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setDelegate:self];
	[request setCompletionBlock:^{
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		//NSLog(@"RESPONSE=%@", jsonString);
		NSDictionary *json = [jsonString JSONValue]; 
		project.projectId = [json objectForKey:@"Id"];
		resultsBlock(project, nil);
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}

@end
