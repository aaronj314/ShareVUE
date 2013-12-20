//
//  ASIHTTPRequestBlocks.h
//  SquishClient
//
//  Created by Aaron Jones on 7/7/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "ASIHTTPRequest.h"
#import "ASIFormDataRequest.h"

typedef void (^ASIRequestFinishedBlock)(ASIHTTPRequest *response);
typedef void (^ASIRequestFailedBlock)(ASIHTTPRequest *failed);
typedef void (^ASIRequestGroupBlock)(void);

@interface ASIHTTPRequest (ASIHTTPRequestBlocks)
-(void)startAsynchronousWithfinishedBlock:(ASIRequestFinishedBlock)finishedBlock failureBlock:(ASIRequestFailedBlock)failureBlock;
-(void)startAsynchronousWithGroup:(dispatch_group_t)group finishedBlock:(ASIRequestFinishedBlock)finishedBlock failureBlock:(ASIRequestFailedBlock)failureBlock groupBlock:(ASIRequestGroupBlock)groupBlock; 
-(void)startAsynchronousWithQueue:(dispatch_queue_t)lqueue finishedBlock:(ASIRequestFinishedBlock)finishedBlock failureBlock:(ASIRequestFailedBlock)failureBlock;
@end
