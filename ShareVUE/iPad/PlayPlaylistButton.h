//
//  PlayPlaylistButton.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/27/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>



@interface PlayPlaylistButton : UIButton {
	Playlist *playlist;
}
@property (nonatomic, retain) Playlist *playlist;
@end
