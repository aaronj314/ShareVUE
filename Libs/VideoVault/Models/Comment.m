//
//  Comment.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "Comment.h"


@implementation Comment
@synthesize created, userId, commentId, sourceVideoId, url, value, userName;
@synthesize timecode;

+(Comment *)commentWithName:(NSString *)n value:(NSString *)v timecode:(double)t {
	Comment *c = [[[Comment alloc] init] autorelease];
	c.userId = n;
	c.value = v;
	c.timecode = t;
	
	//NSDateFormatter *format = [[NSDateFormatter alloc] init];
	//[format setDateFormat:@"yyyy/MM/dd HH:mm:ss"];
	//NSDate *now = [[NSDate alloc] init];
	//NSString *theDate = [format stringFromDate:now];
	
	//c.created = theDate;
	//[format release];
	//[now release];
	return c;
}

-(NSString *)formatedTimecode {
	return [NSString stringWithFormat:@"%02.0f:%02.0f", timecode/60.0, fmodf(timecode, 60)];
}

- (void) dealloc
{
	//NSLog(@"dealloc::%@", [self class]);
    [userName release];
	[created release];
	[userId release];
	[commentId release];
	[sourceVideoId release];
	[url release];
	[value release];
	[super dealloc];
}


#pragma mark -
#pragma mark DEMO CODE
+(NSMutableArray *)commentsForDemo {
	srand(time(0));
	Comment *c1 = [Comment commentWithName:@"Name" value:@"Test comment." timecode:(double)(arc4random() % 10)];
	
	Comment *c2 = [Comment commentWithName:@"Name" value:@"Test comment." timecode:(double)(arc4random() % 10)];
	
	Comment *c3 = [Comment commentWithName:@"Name" value:@"Test comment." timecode:(double)(arc4random() % 10)];
	return [NSMutableArray arrayWithObjects:c1, c2, c3, nil];
}
@end
