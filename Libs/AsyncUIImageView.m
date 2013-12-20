//
//  AsyncUIImageView.m
//  i360Client
//
//  Created by Aaron Jones on 9/17/10.
//

#import "AsyncUIImageView.h"


@implementation AsyncUIImageView


-(void)dealloc {
	[connection cancel]; //in case the URL is still downloading
	[connection release];
	[loadingView release];
	[data release];
	data = nil;
    [super dealloc];
}


- (void)imageViewFromURL:(NSURL*)url {
	if (url==nil) { return;}
	if (connection!=nil) { [connection release]; connection = nil;} //in case we are downloading a 2nd image
	if (data!=nil) { [data release]; data = nil;}
	//self.autoresizingMask = UIViewAutoresizingFlexibleHeight|UIViewAutoresizingFlexibleWidth;
	NSURLRequest* request = [NSURLRequest requestWithURL:url cachePolicy:NSURLRequestUseProtocolCachePolicy timeoutInterval:30.0];
	connection = [[NSURLConnection alloc] initWithRequest:request delegate:self]; 
	//TODO error handling, what if connection is nil?
	//self.alpha = 0.0f;
	//loadingView = [[UIView alloc] initWithFrame:self.frame];
	//loadingView.backgroundColor = [UIColor blackColor];
	//[self addSubview:loadingView];
	
}

//the URL connection calls this repeatedly as data arrives
- (void)connection:(NSURLConnection *)theConnection didReceiveData:(NSData *)incrementalData {
	if (data==nil) { data = [[NSMutableData alloc] initWithCapacity:2048]; } 
	[data appendData:incrementalData];
}

//the URL connection calls this once all the data has downloaded
- (void)connectionDidFinishLoading:(NSURLConnection*)theConnection {
	//so self data now has the complete image 
	[connection release];
	connection=nil;
	self.image = [UIImage imageWithData:data];
	//[UIView animateWithDuration:0.2 animations:^{self.alpha = 1.0f; loadingView.alpha = 0.0f;}];
	
	[data release]; //don't need this any more, its in the UIImageView now
	data=nil;
}

@end
