    //
//  VideoPlayFullViewController.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/30/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "VideoPlayFullViewController.h"
#import "VideoPlayControlsView.h"
#import "VideoPlaybackCommentDelegate.h"
#import "PlayerCommentSliderView.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "PDColoredProgressView.h"
#import "VideoPlaybackView.h"

@implementation VideoPlayFullViewController
@synthesize playButton, delegate, playbackDelegate;
@synthesize video, minScreenButton;
@synthesize uuidWaterMark, userWaterMark, watermark; 

 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
/*
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
    }
    return self;
}
*/

- (void)dealloc {
	//NSLog(@"dealloc::%@", [self class]);
    //NSLog(@"controlsView retain count = %i", [controlsView retainCount]);
	[controlsView release];
	[playButton release];
    //NSLog(@"playbackDelegate retain count = %i", [playbackDelegate retainCount]);
	[playbackDelegate release];
    //[playbackDelegate release];
    
     //NSLog(@"playbackDelegate retain count = %i", [playbackDelegate retainCount]);
    //[playbackDelegate release];
	[minScreenButton release];
	//[delegate release];
	[playButton release];
	[uuidWaterMark release];
	[userWaterMark release];
	[watermark release];
	[delegate release];
    [editBar release];
    [super dealloc];
}


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	//CGAffineTransform rotate = CGAffineTransformMakeRotation(1.57079633);
	//[self.view setTransform:rotate];
	//controlsView.frame = CGRectMake(0, -4, controlsView.frame.size.width, controlsView.frame.size.height);
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	userWaterMark.text = appDelegate.account.user.userName;
	uuidWaterMark.text = [UIDevice currentDevice].uniqueIdentifier;
	
	[self.view addSubview:controlsView];
}

-(void)setDelegate:(id)d {
	if (d != delegate) {
		id temp = delegate;
		delegate = [d retain];
		[temp release];
	}
	minScreenButton.target = delegate;
	minScreenButton.action = @selector(minScreen:);
}



-(void)setPlayerLayer:(UIView *)v {
	//v.frame = self.view.frame;
	v.frame = CGRectMake(0, 0, 1024, 768);
	[(UIView *)[self.view viewWithTag:1] removeFromSuperview];
	[self.view insertSubview:v atIndex:0];
	
	double t = [playbackDelegate getCurrentTime];
	[playbackDelegate setScrubberToTime:t];
	playbackDelegate.watermark = watermark;
}

-(void)loadPlayerView {
	float f = playbackDelegate.commentSlider.progressView.progress;
	controlsView.slider.progressView.progress = f;
	//controlsView.playbackDelegate = playbackDelegate;
	playbackDelegate.commentSlider = controlsView.slider;
	playbackDelegate.currentTime = controlsView.currentTime;
	playbackDelegate.remainingTime = controlsView.remainingTime;
	
	[controlsView.slider addTarget:playbackDelegate action:@selector(beginScrubbing:) forControlEvents:UIControlEventTouchDown];
	[controlsView.slider addTarget:playbackDelegate action:@selector(endScrubbing:) forControlEvents:UIControlEventTouchUpInside];
	[controlsView.slider addTarget:playbackDelegate action:@selector(endScrubbing:) forControlEvents:UIControlEventTouchUpOutside];
	[controlsView.slider addTarget:playbackDelegate action:@selector(scrub:) forControlEvents:UIControlEventValueChanged];
	
	playbackDelegate.mPlayBar = controlsView.playBar;
	playbackDelegate.mPauseBar = controlsView.pauseBar;
	//playbackDelegate.thumbnailView = thumbnail;
	[playbackDelegate syncButtons];
	[playbackDelegate syncScrubber];
}



- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    return ((interfaceOrientation == UIInterfaceOrientationLandscapeLeft) || (interfaceOrientation == UIInterfaceOrientationLandscapeRight));
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation) interfaceOrientation duration:(NSTimeInterval)duration {
    if (interfaceOrientation == UIInterfaceOrientationPortrait || interfaceOrientation ==
        UIInterfaceOrientationPortraitUpsideDown) { 
	}
}



- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.d
    // e.g. self.myOutlet = nil;
}

- (BOOL)textFieldShouldReturn:(UITextField *)textField {
	[commentField resignFirstResponder];
    [self keyboardWillHide];
	return YES;
}


-(IBAction)addTimecodeComment:(id)sender {
	id keyboardImpl = [objc_getClass("UIKeyboardImpl") sharedInstance];
	[keyboardImpl setAlpha:0.6f];
    if ([playbackDelegate isPlaying]) {
        [playbackDelegate pause:self];
    }
	
    [[NSNotificationCenter defaultCenter] removeObserver:self];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide) name:UIKeyboardWillHideNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
    
    /*
	commentField.hidden = NO;
	//commentField.editable = YES;
	[[commentField viewWithTag:52] becomeFirstResponder];
	
	controlsView.hidden = YES;
	
	UIView *parent = commentField;
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDelay:0.20];
	[UIView setAnimationDuration:0.25];
	parent.alpha = 1.0;
	[UIView commitAnimations];
	parent.alpha = 1.0;
    */
    
    //TechnicolorDailiesAppDelegate_iPad *appDelegate = (TechnicolorDailiesAppDelegate_iPad *)[UIApplication sharedApplication].delegate;
    	
    if (!editBar) {
        static NSString *kCellNibName = @"CommentTextBox";
        NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:self options:nil];

        editBar = [[topLevelObjects objectAtIndex:0] retain];
        editBar.frame = CGRectMake(0, 352, editBar.frame.size.width, editBar.frame.size.height);
        UIToolbar *tb = (UIToolbar *)[editBar viewWithTag:10];
        UIBarButtonItem *saveButton = [tb.items objectAtIndex:1];
        saveButton.target = self;
        saveButton.action = @selector(saveComment:);
        [self.view addSubview:editBar];
    }
	
    [[editBar viewWithTag:30] becomeFirstResponder];
	 
}

-(IBAction)playVideo:(id)sender {
	//[controlsView hideControls];
	[playbackDelegate play:sender];
}
-(IBAction)pauseVideo:(id)sender {
	[playbackDelegate pause:sender];
}
-(IBAction)showControls:(id)sender {
}

-(void)keyboardDidShow:(NSNotification *)aNotification {
    NSDictionary* info = [aNotification userInfo];
    
    // Get the size of the keyboard.
    NSValue *aValue = [info objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGRect keyboardFrame = [aValue CGRectValue];
    //NSLog(@"Keyboard Rect=%@", NSStringFromCGRect(keyboardFrame));
    
    [UIView animateWithDuration:0.2 animations:^{
        editBar.alpha = 1.0;
    }];
}

-(void)saveComment:(id)sender {
    UITextField *text = (UITextField *)[editBar viewWithTag:30];
    
    if (![text.text isEqualToString:@""] && text.text != nil) {
        ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
        Comment *comment= [Comment commentWithName:appDelegate.account.user.userName value:text.text timecode:[playbackDelegate getCurrentTime]];
        comment.userName = appDelegate.account.user.userName;
        
        CreateResultsBlock blk = ^(id object, NSError *error) {
            Comment *c = (Comment *)object;
            if (c) {
                comment.userName = appDelegate.account.user.userName;
                NSMutableArray *newComments = [video.comments mutableCopy];
                [newComments addObject:c];
                video.comments = [NSArray arrayWithArray:newComments];
                commentText.text = @"";
            } else {
                NSLog(@"ERROR CREATING COMMENT=%@", error);
            }
            
            
        };
        [appDelegate.account createComment:comment video:video userId:appDelegate.account.user.userId resultsBlock:blk];
        
    }
    text.text = @"";
    [text resignFirstResponder];
    
    
    
} 

-(void)keyboardWillHide {
	id keyboardImpl = [objc_getClass("UIKeyboardImpl") sharedInstance];
	[keyboardImpl setAlpha:1.0f];
	//[playbackDelegate play:self];
	controlsView.hidden = NO;
    [UIView animateWithDuration:0.2 animations:^{
        editBar.alpha = 0.0;
    }];
    /*
	[[NSNotificationCenter defaultCenter] removeObserver:self];
	//commentField.editable = NO;
	[[commentField viewWithTag:52] resignFirstResponder];
	
	UIView *parent = commentField;
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDelay:0.20];
	[UIView setAnimationDuration:0.25];
	parent.alpha = 0.0;
	[UIView commitAnimations];
	parent.alpha = 0.0;
	

	TechnicolorDailiesAppDelegate_iPad *appDelegate = (TechnicolorDailiesAppDelegate_iPad *)[UIApplication sharedApplication].delegate;
	
	Comment *comment= [Comment commentWithName:appDelegate.tcnAccount.user.userName value:commentText.text timecode:[playbackDelegate getCurrentTime]];
	comment.userName = appDelegate.tcnAccount.user.userName;
    
	
	TCNCreateResultsBlock blk = ^(id object, NSError *error) {
        Comment *c = (Comment *)object;
		if (c) {
            comment.userName = appDelegate.tcnAccount.user.userName;
			NSMutableArray *newComments = [video.comments mutableCopy];
			[newComments insertObject:c atIndex:0];
			video.comments = [NSArray arrayWithArray:newComments];
			commentText.text = @"";
		} else {
			NSLog(@"ERROR CREATING COMMENT=%@", error);
		}
		
		
	};
	[appDelegate.tcnAccount createComment:comment video:video resultsBlock:blk];
	*/
}


@end
