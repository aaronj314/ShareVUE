//
//  AsyncUIImageView.h
//  i360Client
//
//  Created by Aaron Jones on 9/17/10.
//

#import <Foundation/Foundation.h>


@interface AsyncUIImageView : UIImageView {
	
	NSURLConnection* connection; //keep a reference to the connection so we can cancel download in dealloc
	NSMutableData* data; //keep reference to the data so we can collect it as it downloads
	//but where is the UIImage reference? We keep it in self.subviews - no need to re-code what we have in the parent class
	
	UIView *loadingView;
	
}

-(void)imageViewFromURL:(NSURL*)url;

@end
