//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/22/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "VideoPlaybackView.h"

#import <AVFoundation/AVFoundation.h>

@implementation VideoPlaybackView


+ (Class)layerClass{
	return [AVPlayerLayer class];
}

- (AVPlayer *)player
{
	return [(AVPlayerLayer *)[self layer] player];
}

- (void)setPlayer:(AVPlayer *)player
{
	[(AVPlayerLayer *)[self layer] setPlayer:player];
}

@end
