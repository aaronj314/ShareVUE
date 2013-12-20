//
//  Account_Video.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Account.h"

typedef void (^VideoURLsResultsBlock)(NSMutableArray *sources, NSError *error);
typedef void (^VideoURLResultsBlock)(NSURL *url, NSError *error);

@interface Account (SourceVideo)
-(void)videosForProject:(Project *)project resultsBlock:(VideosResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock;
-(void)videosUrls:(SourceVideo *)video resultsBlock:(VideoURLsResultsBlock)resultsBlock;
-(void)videoUrl:(SourceVideo *)video preset:(NSString *)preset resulsBlock:(VideoURLResultsBlock)resultsBlock;
-(void)getVideo:(SourceVideo *)video resultsBlock:(GetResultsBlock)resultsBlock;
-(void)getVideoALE:(SourceVideo *)video resultsBlock:(GetResultsBlock)resultsBlock;
-(void)videosForProject:(Project *)project resultsBlock:(VideosResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock aleKey:(NSString *)key aleValue:(NSString *)value;
-(void)createVideo:(SourceVideo *)video resultsBlock:(CreateResultsBlock)resultsBlock;
-(void)updateVideo:(SourceVideo *)video resultsBlock:(UpdateResultsBlock)resultsBlock;
-(void)deleteVideo:(SourceVideo *)video resultsBlock:(DeleteResultsBlock)resultsBlock;
-(void)videoHttpLiveUrl:(SourceVideo *)video resulsBlock:(VideoURLResultsBlock)resultsBlock;
@end
