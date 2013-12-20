//
//  Account+Comments.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account.h"


@interface Account (Comments)
-(void)commentsForVideo:(SourceVideo *)video resultsBlock:(CommentsResultsBlock)resultsBlock;

-(void)createComment:(Comment *)comment video:(SourceVideo *)video userId:(NSString *)userId resultsBlock:(CreateResultsBlock)resultsBlock;
-(void)updateComment:(Comment *)comment resultsBlock:(UpdateResultsBlock)resultsBlock;
-(void)deleteComment:(Comment *)comment resultsBlock:(DeleteResultsBlock)resultsBlock;
@end
