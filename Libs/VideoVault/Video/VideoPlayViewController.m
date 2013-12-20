    //
//  VideoPlayViewController.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 12/29/10.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//

#import "VideoPlayViewController.h"
#import "VideoPlayFullViewController.h"
#import "VideoPlaybackCommentDelegate.h"
#import "PlayerCommentSliderView.h"
#import "VideoPlaybackView.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "MGSplitViewController.h"
#import "RootViewController.h";
#import <QuartzCore/QuartzCore.h>

//#import "CommentEditViewController.h"
//#import "CommentTableViewCell.h"

static CGRect oldRect;

@implementation VideoPlayViewController
@synthesize video;
@synthesize tableView, playbackDelegate;
@synthesize slider;
@synthesize playbackView;
@synthesize titlePanel;
@synthesize currentTime;
@synthesize remainingTime;

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

-(NSURL *)localMovieURL:(NSInteger)i {
	NSURL *url = nil;
	NSBundle *bundle = [NSBundle mainBundle];
	if (bundle) {
		NSString *name = nil;
		switch (i) {
			case 0:
				name = @"demo";
				break;
			case 1:
				name = @"demo2";
				break;
			default:
				break;
		}
		NSString *moviePath = [bundle pathForResource:name ofType:@"MOV"];
		
		if (moviePath)
		{
			url = [NSURL fileURLWithPath:moviePath];
		}
	}
    
    return url;
}

- (void)viewDidAppear:(BOOL)animated {
    CGRect frame = self.view.frame;
    NSLog(@"VideoPlayViewController.frame=%@", NSStringFromCGRect(frame));
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
	//tableView.rowHeight = 84;
	tableView.layer.cornerRadius =10.0f;
	titlePanel.layer.cornerRadius =10.0f;
	//UIView *bgView = [[UIView alloc] initWithFrame:CGRectZero];
	//bgView.backgroundColor = [UIColor colorWithRed:0.2 green:0.2 blue:0.2 alpha:1.0];
	//tableView.backgroundView = bgView;
	//[bgView release];
	
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	userWaterMark.text = appDelegate.account.user.userName;
	uuidWaterMark.text = [UIDevice currentDevice].uniqueIdentifier;
	//playbackView.frame = CGRectMake(0, 0, 703, 368);
	//playbackDelegate.URL = [self localMovieURL:1];
	
	//UIView *top = [[self.view subviews] objectAtIndex:0];
	//UIView *old = [[top subviews] objectAtIndex:0];
	
	//NSLog(@"========= old.frame=%@",NSStringFromCGRect(old.frame));
	tableView.backgroundColor = UIColorFromRGB(0xff3d3d3d);//rgb 61,61,61
	tableView.separatorColor = [UIColor blackColor];
    
    playbackDelegate.currentTime = self.currentTime;
    playbackDelegate.remainingTime = self.remainingTime;
    
    // register for sign out notifications
    [[NSNotificationCenter defaultCenter] addObserverForName:@"SignOutNotification" object:nil queue:nil usingBlock:^(NSNotification *note){
            [playbackDelegate stop:nil];
        }];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    return YES;//((interfaceOrientation == UIInterfaceOrientationLandscapeLeft) || (interfaceOrientation == UIInterfaceOrientationLandscapeRight));
}

- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation duration:(NSTimeInterval)duration {
	//NSLog(@"Rotate 1=%@",NSStringFromCGRect(editBar.frame));
	//CGRect f;
	if (interfaceOrientation == UIInterfaceOrientationPortrait || interfaceOrientation == UIInterfaceOrientationPortraitUpsideDown) {
		//f = CGRectMake(0, 0, 768, 505);
         editBar.frame = CGRectMake(0, 100, editBar.frame.size.width, editBar.frame.size.height);
	} else {
		//f = CGRectMake(0, 0, 703, 368);
         editBar.frame = CGRectMake(0, 308, editBar.frame.size.width, editBar.frame.size.height);
	}
	//NSLog(@"Rotate 11=%@",NSStringFromCGRect(contentController.view.frame));
	
	//playbackView.frame = f;
}

/*
- (void)willAnimateRotationToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation duration:(NSTimeInterval)duration {
	NSLog(@"Rotate 2");
}
*/

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc. that aren't in use.
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
	//NSLog(@"dealloc::%@", [self class]);
	[video release];
    //NSLog(@"================PlaybackDelegateRetainCount=%i", [playbackDelegate retainCount]);
	[videoFullViewController release];
	[playbackDelegate stop:nil];
    
	[playbackDelegate release];
	[slider release];
	[playbackView release];
	[segmentedControl release];
	[playButton release];
	[pauseButton release];
	[tableView release];
	[titlePanel release];
	[watermark release];
	[uuidWaterMark release];
	[userWaterMark release];
    [currentTime release];
    [remainingTime release];
    [super dealloc];
}

-(IBAction)minScreen:(id)sender {
	//videoFullViewController.delegate = nil;
	[tableView reloadData];
	//float f = playbackDelegate.commentSlider.progressView.progress;
	//controlsView.slider.progressView.progress = f;
	playbackDelegate.commentSlider = slider;
	[slider addTarget:playbackDelegate action:@selector(beginScrubbing:) forControlEvents:UIControlEventTouchDown];
	[slider addTarget:playbackDelegate action:@selector(endScrubbing:) forControlEvents:UIControlEventTouchUpInside];
	[slider addTarget:playbackDelegate action:@selector(endScrubbing:) forControlEvents:UIControlEventTouchUpOutside];
	[slider addTarget:playbackDelegate action:@selector(scrub:) forControlEvents:UIControlEventValueChanged];
	
	playbackDelegate.mPlayBar = playButton;
	playbackDelegate.mPauseBar = pauseButton;
	//playbackDelegate.thumbnailView = thumbnail;
	[playbackDelegate syncButtons];
	[playbackDelegate syncScrubber];
	
	//v.frame = self.view.frame;
	UIView *top = [self.view.subviews objectAtIndex:0];
	//UIView *old = [top.subviews objectAtIndex:0];
	//NSLog(@"minScreen::subviews count = %i", [top.subviews count]);
	
	//NSLog(@"old.frame=%@",NSStringFromCGRect(old.frame));
	UIView *playView = playbackDelegate.mPlaybackView;
	playView.frame = oldRect;
	
	//[old removeFromSuperview];
	[top insertSubview:playView atIndex:0];
	//[top addSubview:playView];
	
	
	//[v setNeedsDisplay];
	double t = [playbackDelegate getCurrentTime];
	[playbackDelegate setScrubberToTime:t];
	
	playbackDelegate.watermark = watermark;
	
	ShareVUEAppDelegate_iPad *delegate = APP_IPAD_DELEGATE();
	UIWindow *window = delegate.window;
	NSArray *views = window.subviews;
	UIView *topView = [views objectAtIndex:0];
	
	//UIView *parent = [topView viewWithTag:777];
	
	[topView removeFromSuperview];
	[window addSubview:delegate.rootViewController.view];
	
	
	//[UIView animateWithDuration:0.2 animations:^{
	//	parent.alpha = 0.0;
	//} completion:^(BOOL finished){
	//	[parent removeFromSuperview];
	//}];
	//parent.alpha = 0.0;
    
    playbackDelegate.currentTime = self.currentTime;
    playbackDelegate.remainingTime = self.remainingTime;
}


-(IBAction)fullScreen:(id)sender {
	UIView *top = [self.view viewWithTag:1];
	UIView *old = [top viewWithTag:11];
	oldRect = old.frame;
	
	if (videoFullViewController == nil) {
		videoFullViewController = [[VideoPlayFullViewController alloc] initWithNibName:@"VideoPlayFullViewController" bundle:nil];
		videoFullViewController.playbackDelegate = playbackDelegate;
		
		videoFullViewController.view.tag = 777;
		
	}
	videoFullViewController.delegate = self;
	ShareVUEAppDelegate_iPad *delegate = APP_IPAD_DELEGATE();
	
	
	UIWindow *window = delegate.window;
	NSArray *views = window.subviews;
	UIView *topView = [views objectAtIndex:0];
	[topView removeFromSuperview];

	//UIView *parent = videoFullViewController.view;
	//NSLog(@"fullScreen::subviews count = %i", [top.subviews count]);
	//NSLog(@"fullScreen::old.frame=%@",NSStringFromCGRect(window.frame));
	[window addSubview:videoFullViewController.view];
	
	[videoFullViewController loadPlayerView];
	[videoFullViewController setPlayerLayer:playbackDelegate.mPlaybackView];
	videoFullViewController.video = video;
	//videoFullViewController.playbackDelegate.URL = playbackDelegate.URL;
}

-(void) addComment:(Comment *)comment {
	comment.timecode = [playbackDelegate getCurrentTime];
    ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    //comment.userName = delegate.tcnAccount.user.userName;
	//NSLog(@"%f", [playbackDelegate getCurrentTime]);
    comment.userName = appDelegate.account.user.userName;
	CreateResultsBlock blk = ^(id object, NSError *error) {
        Comment *c = (Comment *)object;
		if (c) {
			NSMutableArray *newComments = [video.comments mutableCopy];
			[newComments addObject:c];
            
            NSArray *sortedArray = [newComments sortedArrayUsingComparator: ^(id obj1, id obj2) {
                Comment *c1 = (Comment *)obj1;
                Comment *c2 = (Comment *)obj2;
                
                if (c1.timecode > c2.timecode) {
                    return (NSComparisonResult)NSOrderedDescending;
                }
                
                if (c1.timecode < c2.timecode) {
                    return (NSComparisonResult)NSOrderedAscending;
                }
                return (NSComparisonResult)NSOrderedSame;
            }];
            
			//video.comments = [NSArray arrayWithArray:newComments];
            NSMutableArray *mArray = [sortedArray mutableCopy];
            video.comments = mArray;
            [mArray release];
            [newComments release];
			[tableView reloadData];
		} else {
			NSLog(@"ERROR CREATING COMMENT=%@", error);
		}

		
	};
	comment.userName = appDelegate.account.user.userName;
	[appDelegate.account createComment:comment video:video userId:appDelegate.account.user.userId resultsBlock:blk];
	
	if (wasPlaying) {
		[playbackDelegate play:self];
	}
	
}

-(void) saveComment:(id)sender {
    UITextField *text = (UITextField *)[editBar viewWithTag:30];
    
    if (![text.text isEqualToString:@""] && text.text != nil) {
        Comment *commet = [Comment commentWithName:nil value:text.text timecode:0.0];
        [self addComment:commet];
        
    }
    text.text = @"";
    [text resignFirstResponder];
}

-(IBAction)addCommentForTimecode:(id)sender {
    [[NSNotificationCenter defaultCenter] removeObserver:self];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidHide:) name:UIKeyboardDidHideNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
	wasPlaying = [playbackDelegate isPlaying];
	[playbackDelegate pause:self];
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	//CommentEditViewController *controller = [[CommentEditViewController alloc] initWithNibName:@"CommentEditViewController" bundle:nil];
	//controller.modalPresentationStyle = UIModalPresentationFormSheet;
	///controller.modalTransitionStyle = UIModalTransitionStyleCrossDissolve;
	//controller.modalController = self;
	//controller.timecode.text = [NSString stringWithFormat:@"%d", [playbackDelegate getCurrentTime]];
	//[self presentModalViewController:controller animated:YES];
	//[controller release];
    
    
	
    if (!editBar) {
        static NSString *kCellNibName = @"CommentTextBox";
        NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:self options:nil];
        editBar = [[topLevelObjects objectAtIndex:0] retain];
        editBar.frame = CGRectMake(0, 308, editBar.frame.size.width, editBar.frame.size.height);
        UIToolbar *tb = (UIToolbar *)[editBar viewWithTag:10];
        UIBarButtonItem *saveButton = [tb.items objectAtIndex:1];
        saveButton.target = self;
        saveButton.action = @selector(saveComment:);
    }
	[appDelegate.splitViewController.view addSubview:editBar];
    [[editBar viewWithTag:30] becomeFirstResponder];
    
}

-(void)keyboardDidShow:(NSNotification *)aNotification {
    NSDictionary* info = [aNotification userInfo];
    ///TechnicolorDailiesAppDelegate_iPad *delegate = (TechnicolorDailiesAppDelegate_iPad *)[UIApplication sharedApplication].delegate;
    // Get the size of the keyboard.
    NSValue *aValue = [info objectForKey:UIKeyboardFrameEndUserInfoKey];
    CGRect keyboardFrame = [aValue CGRectValue];
    //NSLog(@"SHOW Keyboard Rect=%@", NSStringFromCGRect(keyboardFrame));
    
    [UIView animateWithDuration:0.2 animations:^{
        editBar.alpha = 1.0;
    }];
    
   
    
}

-(void)keyboardDidHide:(NSNotification *)aNotification {
    //NSLog(@"DID HIDE KEYBOARD");
}

-(void)keyboardWillHide:(NSNotification *)aNotification {
    //NSLog(@"HIDE Keyboard");
	//TechnicolorDailiesAppDelegate_iPad *delegate = (TechnicolorDailiesAppDelegate_iPad *)[UIApplication sharedApplication].delegate;
	//[[NSNotificationCenter defaultCenter] removeObserver:self];
    //[[delegate.window viewWithTag:0] removeFromSuperview];
	
	[UIView animateWithDuration:0.2 animations:^{
        editBar.alpha = 0.0;
    } completion:^(BOOL finished){ 
        [editBar removeFromSuperview]; 
    }];
}

-(IBAction)editComments:(id)sender {
    [self.tableView setEditing:YES animated:YES];
    editButton.title = @"Done";
    editButton.action = @selector(doneEditComments:);
}

-(void)doneEditComments:(id)sender {
    [self.tableView setEditing:NO animated:YES];
    editButton.title = @"Edit";
    editButton.action = @selector(editComments:);
}

#pragma mark -
#pragma mark Table view data source

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}


// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    //return [video.comments count];
    switch (segmentedControl.selectedSegmentIndex) {
        case 0:
            return [video.comments count];
        case 1:
            return [video.metadata count];
        default:
            return 0;
    }
}


-(UITableViewCell *)cellForComment:(NSIndexPath *)indexPath {
    UITableViewCell *cell = nil;
    static NSString *kDisplayCell_ID = @"VideoCommentDisplayCellID";
	cell = [self.tableView dequeueReusableCellWithIdentifier:kDisplayCell_ID];
	if (cell == nil) {
		cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kDisplayCell_ID] autorelease];
		cell.selectionStyle = UITableViewCellSelectionStyleGray;
		//cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	}
	Comment *c = [video.comments objectAtIndex:[indexPath row]];
	//TechnicolorDailiesAppDelegate_iPad *appDelegate = (TechnicolorDailiesAppDelegate_iPad *)[UIApplication sharedApplication].delegate;
	cell.textLabel.text = [NSString stringWithFormat:@"%@ - %@ (%@)", c.userName, [c formatedTimecode], c.created];
	cell.textLabel.textColor = [UIColor whiteColor];
	cell.detailTextLabel.text = c.value;
    cell.detailTextLabel.textColor = [UIColor whiteColor];
    return cell;
}

-(UITableViewCell *)cellForMetadata:(NSIndexPath *)indexPath {
    UITableViewCell *cell = nil;
    static NSString *kDisplayCell_ID = @"MetadataDisplayCellID";
	cell = [self.tableView dequeueReusableCellWithIdentifier:kDisplayCell_ID];
	if (cell == nil) {
		cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kDisplayCell_ID] autorelease];
		cell.selectionStyle = UITableViewCellSelectionStyleGray;
		//cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	}
	SMetadata *md = [video.metadata objectAtIndex:[indexPath row]];
	//TechnicolorDailiesAppDelegate_iPad *appDelegate = (TechnicolorDailiesAppDelegate_iPad *)[UIApplication sharedApplication].delegate;
	cell.textLabel.text = [NSString stringWithFormat:@"%@ - %@", md.name, md.value];
	cell.textLabel.textColor = [UIColor whiteColor];
    return cell;
    
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	//UITableViewCell *cell = nil;
    /*
	static NSString *kDisplayCell_ID = @"VideoCommentDisplayCellID";
	cell = [self.tableView dequeueReusableCellWithIdentifier:kDisplayCell_ID];
	if (cell == nil) {
		cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:kDisplayCell_ID] autorelease];
		cell.selectionStyle = UITableViewCellSelectionStyleGray;
		//cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
	}
	Comment *c = [video.comments objectAtIndex:[indexPath row]];
	//TechnicolorDailiesAppDelegate_iPad *appDelegate = (TechnicolorDailiesAppDelegate_iPad *)[UIApplication sharedApplication].delegate;
	cell.textLabel.text = [NSString stringWithFormat:@"%@ - %@ (%@)", c.userName, [c formatedTimecode], c.created];
	cell.textLabel.textColor = [UIColor whiteColor];
	cell.detailTextLabel.text = c.value;
	 cell.detailTextLabel.textColor = [UIColor whiteColor];
	*/
    
    if (segmentedControl.selectedSegmentIndex == 0) {
        return [self cellForComment:indexPath];
    } else if (segmentedControl.selectedSegmentIndex == 1) {
        return [self cellForMetadata:indexPath];
    } else {
        return nil;
    }
	//return cell;
}

/*
 // Override to support conditional editing of the table view.
 - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the specified item to be editable.
 return YES;
 }
 */



 // Override to support editing the table view.
 - (void)tableView:(UITableView *)table commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
 
     if (editingStyle == UITableViewCellEditingStyleDelete) {
         // Delete the row from the data source.
         Comment *c = [[video.comments objectAtIndex:indexPath.row] retain];
         [video.comments removeObjectAtIndex:indexPath.row];
         [table deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
         
         ShareVUEAppDelegate_iPad *delegate = APP_IPAD_DELEGATE();
		 DeleteResultsBlock blk = ^(id object, NSError *error) {
             [tableView reloadData];
         };
         [delegate.account deleteComment:c resultsBlock:nil];
     }   
     else if (editingStyle == UITableViewCellEditingStyleInsert) {
         // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
     }   
 }
 


/*
 // Override to support rearranging the table view.
 - (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
 }
 */


/*
 // Override to support conditional rearranging of the table view.
 - (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the item to be re-orderable.
 return YES;
 }
 */


#pragma mark -
#pragma mark Table view delegate
- (CGFloat)tableView:(UITableView *)tableView heightForHeaderInSection:(NSInteger)section {
    return  1;
}

-(UIView *)sectionHeaderView:(NSString *)text {
    static NSString *kCellNibName = @"BaseTableHeaderView";
	NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:self options:nil];
    UIView *v = [topLevelObjects objectAtIndex:0];
    UILabel *label = (UILabel *)[v viewWithTag:1];
    label.text = text;
    return v;
	
}

/*
-(UIView *)tableView:(UITableView *)tableView viewForHeaderInSection:(NSInteger)section {
	if (section == 0) {
		return [self sectionHeaderView:@"Video Comments:"];
	} 
	
	
}
*/

- (void)tableView:(UITableView *)table didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	[table deselectRowAtIndexPath:indexPath animated:YES];
	Comment *c = [video.comments objectAtIndex:indexPath.row];
	[playbackDelegate setScrubberToTime:c.timecode];
}

/*
 - (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
 return 1.0f;
 }
 */

-(void)showCommentsTableView {
    //tableView.hidden = NO;
    //videoMetaData.hidden = YES;
    UILabel *title = [titlePanel viewWithTag:1];
    title.text = @"Video Comments";
    UIButton *addCommentButton = [titlePanel viewWithTag:2];
    addCommentButton.hidden = NO;
    [tableView reloadData];
    tableView.separatorStyle = UITableViewCellSeparatorStyleSingleLine;
}

-(void)showMetadataView {
    //tableView.hidden = YES;
    //videoMetaData.hidden = NO;
    UILabel *title = [titlePanel viewWithTag:1];
    title.text = @"Video Details";
    UIButton *addCommentButton = [titlePanel viewWithTag:2];
    addCommentButton.hidden = YES;
    [tableView reloadData];
    tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
}

-(IBAction) segmentedControlIndexChanged:(id)sender {
	switch (segmentedControl.selectedSegmentIndex) {
        case 0:
            [self showCommentsTableView];
            break;
        case 1:
            [self showMetadataView];
            break;
        default:
            break;
    }
}
@end
