//
//  Account.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/13/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account.h"
#import "User.h"
#import "Project.h"
#import "Playlist.h"
#import "SourceVideo.h"
#import "Asset.h"

#import "JSON.h"
#import "ASIHTTPRequest.h"
#import "ASIFormDataRequest.h"

//static NSString * const _BACKEND_HOST = @"http://dev-videovault.sorensonmedia.com/vapi/";
//static NSString * const X_AUTH_TOKEN = @"X-Videovault-Auth-Token";

@implementation Account
@synthesize user;

+(void)signInWithUsername:(NSString *)username password:(NSString *)password resultsBlock:(SignInResultsBlock)resultsBlock; {
	NSString *authAPI = [NSString stringWithFormat:@"%@accounts/authenticate/", _BACKEND_HOST];
	NSURL *url = [NSURL URLWithString:authAPI];
	
	__block ASIHTTPRequest *request = [ASIHTTPRequest requestWithURL:url];
    //[request setValidatesSecureCertificate:NO];
	[request setUseSessionPersistence:NO];
	[request setUsername:username];
	[request setPassword:password];
	[request setRequestMethod:@"POST"];
	[request addRequestHeader:@"Accept" value:@"application/json"];
	[request setContentLength:0];
	[request setDelegate:self];
	
	SMLOG(@"Starting signInWithUsername request %@",self);
	
	
	[request setCompletionBlock:^{
		NSString *token = [[request responseHeaders] objectForKey:X_AUTH_TOKEN];
		
		NSData *data = [request responseData];
		NSString *jsonString = [[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding];
		NSDictionary *results = [jsonString JSONValue];
		
		

		SMLOG(@"Recieved signInWithUsername headers=%@", [request responseHeaders]);
		SMLOG(@"Recieved signInWithUsername data=%@", [request responseString]);
		
		if (!token) {
			token = @"blah";
		}
		
		Account *account = [[[Account alloc] init] autorelease];
		User *u = [[[User alloc] init] autorelease];
		u.token = token;
		u.userName = username;
		u.fullName = [results objectForKey:@"FullName"];
		u.userId = [[results objectForKey:@"Id"] stringValue];
		u.groupId = [[results objectForKey:@"GroupId"] stringValue];
		account.user = u;
		resultsBlock(account, nil);
        [jsonString release];
	}];
	
	[request setFailedBlock:^{
		NSError *error = [request error];
		resultsBlock(nil, error);
	}];
	
	[request startAsynchronous];
}



- (void) dealloc {
	//NSLog(@"dealloc::%@", [self class]);
	[user release];
	[super dealloc];
}


@end
