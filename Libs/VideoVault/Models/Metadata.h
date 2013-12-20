//
//  Metadata.h
//  ShareVUE
//
//  Created by Aaron Jones on 4/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>


@interface SMetadata : NSObject {
    NSString *metadataId;
    NSString *name;
    NSString *value;
}
@property (nonatomic, retain) NSString *metadataId;
@property (nonatomic, retain) NSString *name;
@property (nonatomic, retain) NSString *value;
@end
