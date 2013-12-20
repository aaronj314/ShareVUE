//
//  Asset.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface Asset : NSObject {
	NSString *assetId, *name, *projectId;
	NSURL *url;
}
@property (nonatomic, retain) NSString *assetId, *name, *projectId;
@property (nonatomic, retain) NSURL *url;

// demo code
+(NSMutableArray *)assetsForDemo;
@end
