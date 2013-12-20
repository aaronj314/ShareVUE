//
//  Account+Projects.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/19/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account.h"


@interface Account (Projects)
-(void)accountProjects:(ProjectsResultsBlock)resultsBlock startedBlock:(BasicBlock)startedBlock;
-(void)getProject:(Project *)project resultsBlock:(GetResultsBlock)resultsBlock;
-(void)createProject:(Project *)project resultsBlock:(CreateResultsBlock)resultsBlock;
-(void)updateProject:(Project *)project resultsBlock:(UpdateResultsBlock)resultsBlock;
-(void)deleteProject:(Project *)project resultsBlock:(DeleteResultsBlock)resultsBlock;
-(void)projectAleKeysForProject:(Project *)project resultsBlock:(GetResultsBlock)resultsBlock;
-(void)projectAleKeysForProject:(Project *)project resultsBlock:(GetResultsBlock)resultsBlock;
-(void)projectAleValuesForProject:(Project *)project key:(NSString *)key resultsBlock:(GetResultsBlock)resultsBlock;
@end
