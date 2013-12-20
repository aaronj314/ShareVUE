//
//  ASIHTTPRequestBlocks.m
//  
//
//  Created by Aaron Jones on 7/7/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "ASIHTTPRequestBlocks.h"

@implementation ASIHTTPRequest (ASIHTTPRequestBlocks)

-(void)startAsynchronousWithfinishedBlock:(ASIRequestFinishedBlock)finishedBlock failureBlock:(ASIRequestFailedBlock)failureBlock {
	
	
	
	//if (_queue) {
	//	dispatch_release(_queue);
	//	NSLog(@"RELEASEING HTTP QUEUE===========");
	//}
	//dispatch_queue_t _queue = dispatch_queue_create("sm.http.reqblock.queue",NULL);
	
	//dispatch_async(dispatch_queue_create("sm.http.reqblock.queue",NULL), ^{
	dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
		NSError *error_;
		[self startSynchronous]; 
		
		error_ = [self error];
		if (!error_) {
			//dispatch_async(dispatch_get_main_queue(), ^{finishedBlock(self);});
			//dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{finishedBlock(self);});
			finishedBlock(self);
		} else {
			failureBlock(self);
		}
		
		//dispatch_release(_queue);
	} );

}

-(void)startAsynchronousWithGroup:(dispatch_group_t)group finishedBlock:(ASIRequestFinishedBlock)finishedBlock failureBlock:(ASIRequestFailedBlock)failureBlock groupBlock:(ASIRequestGroupBlock)groupBlock {
	dispatch_group_async(group,dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{
		NSError *error_;
		[self startSynchronous]; 
		
		error_ = [self error];
		if (!error_) {
			//dispatch_async(dispatch_get_main_queue(), ^{finishedBlock(self);});
			//dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_HIGH, 0), ^{finishedBlock(self);});
			finishedBlock(self);
		} else {
			failureBlock(self);
		}
		
		//dispatch_release(_queue);
	} );
}

-(void)startAsynchronousWithQueue:(dispatch_queue_t)lqueue finishedBlock:(ASIRequestFinishedBlock)finishedBlock failureBlock:(ASIRequestFailedBlock)failureBlock {
	dispatch_async(lqueue, ^{
		NSError *error_;
		[self startSynchronous]; 
		
		error_ = [self error];
		if (!error_) {
			finishedBlock(self);
		} else {
			failureBlock(self);
		}
	} );
}

@end
