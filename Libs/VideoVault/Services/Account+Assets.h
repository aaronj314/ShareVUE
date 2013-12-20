//
//  Account+Assets.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/18/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Account.h"


@interface Account (Assets)
-(void)assetsForProject:(Project *)project resultsBlock:(AssetsResultsBlock)resultsBlock;

-(void)accountAssets:(AssetsResultsBlock)resultsBlock;
-(void)createAsset:(Asset *)asset resultsBlock:(CreateResultsBlock)resultsBlock;
-(void)updateAsset:(Asset *)asset resultsBlock:(UpdateResultsBlock)resultsBlock;
-(void)deleteAsset:(Asset *)asset resultsBlock:(DeleteResultsBlock)resultsBlock;
@end
 