//
//  Comment.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface Comment : NSObject {
	NSString *created, *userId, *commentId, *sourceVideoId, *url, *value, *userName;
	double timecode;
}
@property (nonatomic, retain) NSString *created, *userId, *commentId, *sourceVideoId, *url, *value, *userName;
@property (nonatomic) double timecode;
+(Comment *)commentWithName:(NSString *)name value:(NSString *)value timecode:(double)timecode;
-(NSString *)formatedTimecode;

// Demo code
+(NSMutableArray *)commentsForDemo;
@end
