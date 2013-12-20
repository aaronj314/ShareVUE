//
//  VideoPlayerView.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 2/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "VideoPlayerView.h"


@implementation VideoPlayerView

+(Class)layerClass {
    return [AVPlayerLayer class];
}

-(AVPlayer*)player {
	
    return [(AVPlayerLayer *)[self layer] player];
	
}

-(void)setPlayer:(AVPlayer *)player {
	
    [(AVPlayerLayer *)[self layer] setPlayer:player];
	
}

- (void)dealloc {
    [super dealloc];
}


@end
