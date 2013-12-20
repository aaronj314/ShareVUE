//
//  ProjectVideosGridViewController.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ProjectVideosGridViewController.h"
#import "ProjectVideosGridViewCell.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "AsyncUIImageView.h"
#import "VideoPlayViewController.h"
#import "VideoPlaybackCommentDelegate.h"
#import "ContentDetailViewController.h"
#import "ProjectVideoListViewController_iPad.h"
#import "VideoPlayFullViewController.h"
#import "RootViewController.h"
#import "CookieNavView.h"
#import "ProjectMaterialsGridView.h"
#import "FilterSelectViewController.h"

static BOOL isShowingFilterList;

@implementation ProjectVideosGridViewController
@synthesize project;
@synthesize projectName;
@synthesize videos;
@synthesize segmentControl;
@synthesize gridView;
@synthesize signOutButton;
@synthesize contentDetailViewController;
@synthesize aleKeySelectBox;
@synthesize aleValueSelectBox;
@synthesize filterSelectViewController;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
	[videos release];
    [materialsGridView release];
	[contentDetailViewController release];
	[projectName release];
    [project release];
    [gridView release];
    [signOutButton release];
    [segmentControl release];
    [aleKeySelectBox release];
    [aleValueSelectBox release];
    [filterSelectViewController release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    signOutButton.target = APP_DELEGATE().signInViewController;
    signOutButton.action = @selector(signOut:);
	
	projectName.text = project.name;
    
    emptyCellIndex = NSNotFound;
    
    self.view.autoresizesSubviews = YES;
    // background goes in first
    //UIImageView * background = [[UIImageView alloc] initWithFrame: self.view.bounds];
    //background.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
    //background.contentMode = UIViewContentModeCenter;
    //background.image = [UIImage imageNamed: @"background.png"];
    
    //[self.view addSubview: background];
    
    // grid view sits on top of the background image
    //gridView = [[AQGridView alloc] initWithFrame: self.view.bounds];
    gridView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
    gridView.backgroundColor = [UIColor clearColor];
    gridView.opaque = NO;
    gridView.dataSource = self;
    gridView.delegate = self;
    gridView.scrollEnabled = YES;
   
    
    if ( UIInterfaceOrientationIsLandscape([[UIApplication sharedApplication] statusBarOrientation]) )
    {
        // bring 1024 in to 1020 to make a width divisible by five
        gridView.leftContentInset = 2.0;
        gridView.rightContentInset = 2.0;
    }
    
    [self.view addSubview: gridView];
    
    // add our gesture recognizer to the grid view
    UILongPressGestureRecognizer * gr = [[UILongPressGestureRecognizer alloc] initWithTarget: self action: @selector(moveActionGestureRecognizerStateChanged:)];
    gr.minimumPressDuration = 0.5;
    gr.delegate = self;
	//[gridView addGestureRecognizer: gr];
    [gr release];
    
    [gridView reloadData];
    
    filterSelectViewController = [[FilterSelectViewController alloc] initWithNibName:nil bundle:nil];
    filterSelectViewController.view.frame = CGRectMake(488,50,274, 388);
    filterSelectViewController.project = project;
    filterSelectViewController.delegate = self;
    
    UIImageView *downArrow = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"downarrow.gif"]];
    aleKeySelectBox.rightView = downArrow;
    aleKeySelectBox.rightViewMode = UITextFieldViewModeAlways;
    [downArrow release];
}

- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
    [gridView release]; gridView = nil;
}

-(BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
	return YES;
}

-(void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration {
    if ( UIInterfaceOrientationIsPortrait(toInterfaceOrientation) )
    {
        // width will be 768, which divides by four nicely already
       // NSLog( @"Setting left+right content insets to zero" );
        gridView.leftContentInset = 0.0;
        gridView.rightContentInset = 0.0;
		
    }
    else
    {
        // width will be 1024, so subtract a little to get a width divisible by five
        //NSLog( @"Setting left+right content insets to 2.0" );
        gridView.leftContentInset = 2.0;
        gridView.rightContentInset = 2.0;
    }
}

#pragma mark -
#pragma mark UIGestureRecognizer Delegate/Actions
/*
-(void)fetchSourceVideo:(SourceVideo *)v {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	VideoURLResultsBlock blk = ^(NSURL *url, NSError *error){
        NSURL *t = [NSURL URLWithString:@"http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8"];
		self.videoPlayViewController.playbackDelegate.URL = t;
		
	};
	
	//[appDelegate.tcnAccount videosUrls:v resultsBlock:blk];
	[appDelegate.account videoUrl:v preset:nil resulsBlock:blk];
}
*/
 
- (void) gridView: (AQGridView *) gridView didSelectItemAtIndex: (NSUInteger) index {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	NSString *myLabelText = @"<  Back To Project Details"; 
    CookieNav *cookie = [[CookieNav alloc] init];
	cookie.master = appDelegate.splitViewController.masterViewController;
   // ContentDetailViewController *cdetail = (ContentDetailViewController *)appDelegate.splitViewController.detailViewController;
	cookie.detail = self;
	cookie.masterBeforeDetail = NO;
    [appDelegate.rootViewController.cookieNavView pushWithTitle:myLabelText cookie:cookie];
	
	[gridView deselectItemAtIndex:index animated:NO];
	
	//dispatch_async(dispatch_get_main_queue(), ^{
		
		//dispatch_async(dispatch_get_main_queue(), ^{
           
			//[appDelegate.splitViewController toggleMasterView:self];
			ProjectVideoListViewController_iPad *controller = [[ProjectVideoListViewController_iPad alloc] initWithStyle:UITableViewStylePlain];
			controller.videos = videos;
    cookie.delegate = controller;
			controller->selectedIdx = index;
			controller.contentDetailViewController = self.contentDetailViewController;
			appDelegate.splitViewController.masterViewController = controller;
			//appDelegate.splitViewController.detailViewController.view.frame = CGRectMake(0, 0, 600, 1024);
			[controller release];
            [appDelegate.splitViewController toggleMasterBeforeDetail:self];
			//dispatch_async(dispatch_get_main_queue(), ^{
				//appDelegate.splitViewController.masterBeforeDetail = YES;
				//dispatch_async(dispatch_get_main_queue(), ^{ 
				//	[appDelegate.splitViewController toggleMasterView:self];
			//	});
			//});
		//});
	//});
	/*
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	videoFullViewController = [[VideoPlayFullViewController alloc] initWithNibName:@"VideoPlayFullViewController" bundle:nil];
	VideoPlaybackCommentDelegate *playbackDelegate = [[VideoPlaybackCommentDelegate alloc] init];
	videoFullViewController.playbackDelegate = playbackDelegate;
	[playbackDelegate release];
		
	videoFullViewController.view.tag = 777;
		
	videoFullViewController.delegate = self;
	
	
	UIWindow *window = appDelegate.window;
	NSArray *views = window.subviews;
	UIView *topView = [views objectAtIndex:0];
	[topView removeFromSuperview];
	[window addSubview:videoFullViewController.view];
	videoFullViewController.playbackDelegate.mPlaybackView = [videoFullViewController.view viewWithTag:1];
	[videoFullViewController loadPlayerView];
	videoFullViewController.video = [videos objectAtIndex:index];
	
	VideoURLResultsBlock blk = ^(NSURL *url, NSError *error){
        //NSURL *t = [NSURL URLWithString:@"http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8"];
		videoFullViewController.playbackDelegate.URL = url;
		
	};
	
	//[appDelegate.tcnAccount videosUrls:v resultsBlock:blk];
	[appDelegate.account videoUrl:[videos objectAtIndex:index] preset:nil resulsBlock:blk];
	 */
    [cookie release];
}

-(void)minScreen:(id)sender {
	[videoFullViewController.playbackDelegate pause:self];
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	UIWindow *window = appDelegate.window;
	NSArray *views = window.subviews;
	UIView *topView = [views objectAtIndex:0];
	
	NSLog(@"VideoFullView retainCount=%i",[videoFullViewController retainCount]);
	[topView removeFromSuperview];
	[window addSubview:appDelegate.rootViewController.view];
	
	NSLog(@"VideoFullView retainCount=%i",[videoFullViewController retainCount]);
	[videoFullViewController release];
	videoFullViewController = nil;
	
}


- (BOOL) gestureRecognizerShouldBegin: (UIGestureRecognizer *) gestureRecognizer
{
    CGPoint location = [gestureRecognizer locationInView: gridView];
    if ( [gridView indexForItemAtPoint: location] < [videos count] )
        return ( YES );
    
    // touch is outside the bounds of any icon cells, so don't start the gesture
    return ( NO );
}

-(void)moveActionGestureRecognizerStateChanged:(UIGestureRecognizer *)recognizer {
    switch ( recognizer.state )
    {
        default:
        case UIGestureRecognizerStateFailed:
            // do nothing
            break;
            
        case UIGestureRecognizerStatePossible:
        case UIGestureRecognizerStateCancelled:
        {
            [gridView beginUpdates];
            
            if ( emptyCellIndex != dragOriginIndex )
            {
                [gridView moveItemAtIndex: emptyCellIndex toIndex: dragOriginIndex withAnimation: AQGridViewItemAnimationFade];
            }
            
            emptyCellIndex = dragOriginIndex;
            
            // move the cell back to its origin
            [UIView beginAnimations: @"SnapBack" context: NULL];
            [UIView setAnimationCurve: UIViewAnimationCurveEaseOut];
            [UIView setAnimationDuration: 0.5];
            [UIView setAnimationDelegate: self];
            [UIView setAnimationDidStopSelector: @selector(finishedSnap:finished:context:)];
            
            CGRect f = draggingCell.frame;
            f.origin = dragOriginCellOrigin;
            draggingCell.frame = f;
            
            [UIView commitAnimations];
            
            [gridView endUpdates];
            
            break;
        }
            
        case UIGestureRecognizerStateEnded:
        {
            CGPoint p = [recognizer locationInView: gridView];
            NSUInteger index = [gridView indexForItemAtPoint: p];
			if ( index == NSNotFound )
			{
				// index is the last available location
				index = [videos count] - 1;
			}
            
            // update the data store
            id obj = [[videos objectAtIndex: dragOriginIndex] retain];
            [videos removeObjectAtIndex: dragOriginIndex];
            [videos insertObject: obj atIndex: index];
            [obj release];
            
            if ( index != emptyCellIndex )
            {
                [gridView beginUpdates];
                [gridView moveItemAtIndex: emptyCellIndex toIndex: index withAnimation: AQGridViewItemAnimationFade];
                emptyCellIndex = index;
                [gridView endUpdates];
            }
            
            // move the real cell into place
            [UIView beginAnimations: @"SnapToPlace" context: NULL];
            [UIView setAnimationCurve: UIViewAnimationCurveEaseOut];
            [UIView setAnimationDuration: 0.5];
            [UIView setAnimationDelegate: self];
            [UIView setAnimationDidStopSelector: @selector(finishedSnap:finished:context:)];
            
            CGRect r = [gridView rectForItemAtIndex: emptyCellIndex];
            CGRect f = draggingCell.frame;
            f.origin.x = r.origin.x + floorf((r.size.width - f.size.width) * 0.5);
            f.origin.y = r.origin.y + floorf((r.size.height - f.size.height) * 0.5);
            NSLog( @"Gesture ended-- moving to %@", NSStringFromCGRect(f) );
            draggingCell.frame = f;
            
            draggingCell.transform = CGAffineTransformIdentity;
            draggingCell.alpha = 1.0;
            
            [UIView commitAnimations];
            break;
        }
            
        case UIGestureRecognizerStateBegan:
        {
            NSUInteger index = [gridView indexForItemAtPoint: [recognizer locationInView: gridView]];
            emptyCellIndex = index;    // we'll put an empty cell here now
            
            // find the cell at the current point and copy it into our main view, applying some transforms
            AQGridViewCell * sourceCell = [gridView cellForItemAtIndex: index];
            CGRect frame = [self.view convertRect: sourceCell.frame fromView: gridView];
            draggingCell = [[ProjectVideosGridViewCell alloc] initWithFrame: frame reuseIdentifier: @""];
            draggingCell.iconView = [videos objectAtIndex: index];
            [self.view addSubview: draggingCell];
            
            // grab some info about the origin of this cell
            dragOriginCellOrigin = frame.origin;
            dragOriginIndex = index;
            
            [UIView beginAnimations: @"" context: NULL];
            [UIView setAnimationDuration: 0.2];
            [UIView setAnimationCurve: UIViewAnimationCurveEaseOut];
            
            // transformation-- larger, slightly transparent
            draggingCell.transform = CGAffineTransformMakeScale( 1.2, 1.2 );
            draggingCell.alpha = 0.7;
            
            // also make it center on the touch point
            draggingCell.center = [recognizer locationInView: self.view];
            
            [UIView commitAnimations];
            
            // reload the grid underneath to get the empty cell in place
            [gridView reloadItemsAtIndices: [NSIndexSet indexSetWithIndex: index]
							 withAnimation: AQGridViewItemAnimationNone];
            
            break;
        }
            
        case UIGestureRecognizerStateChanged:
        {
            // update draging cell location
            draggingCell.center = [recognizer locationInView: self.view];
            
            // don't do anything with content if grid view is in the middle of an animation block
            if ( gridView.isAnimatingUpdates )
                break;
            
            // update empty cell to follow, if necessary
            NSUInteger index = [gridView indexForItemAtPoint: [recognizer locationInView: gridView]];
			
			// don't do anything if it's over an unused grid cell
			if ( index == NSNotFound )
			{
				// snap back to the last possible index
				index = [videos count] - 1;
			}
			
            if ( index != emptyCellIndex )
            {
                NSLog( @"Moving empty cell from %u to %u", emptyCellIndex, index );
                
                // batch the movements
                [gridView beginUpdates];
                
                // move everything else out of the way
                if ( index < emptyCellIndex )
                {
                    for ( NSUInteger i = index; i < emptyCellIndex; i++ )
                    {
                        NSLog( @"Moving %u to %u", i, i+1 );
                        [gridView moveItemAtIndex: i toIndex: i+1 withAnimation: AQGridViewItemAnimationFade];
                    }
                }
                else
                {
                    for ( NSUInteger i = index; i > emptyCellIndex; i-- )
                    {
                        NSLog( @"Moving %u to %u", i, i-1 );
                        [gridView moveItemAtIndex: i toIndex: i-1 withAnimation: AQGridViewItemAnimationFade];
                    }
                }
                
                [gridView moveItemAtIndex: emptyCellIndex toIndex: index withAnimation: AQGridViewItemAnimationFade];
                emptyCellIndex = index;
                
                [gridView endUpdates];
            }
            
            break;
        }
    }
}

- (void) finishedSnap: (NSString *) animationID finished: (NSNumber *) finished context: (void *) context
{
    NSIndexSet * indices = [[NSIndexSet alloc] initWithIndex: emptyCellIndex];
    emptyCellIndex = NSNotFound;
    
    // load the moved cell into the grid view
    [gridView reloadItemsAtIndices: indices withAnimation: AQGridViewItemAnimationNone];
    
    // dismiss our copy of the cell
    [draggingCell removeFromSuperview];
    [draggingCell release];
    draggingCell = nil;
    
    [indices release];
}

#pragma mark -
#pragma mark GridView Data Source

-(NSUInteger)numberOfItemsInGridView:(AQGridView *)gridView {
    return ( [videos count] );
}

-(AQGridViewCell *)gridView:(AQGridView *)gridView cellForItemAtIndex:(NSUInteger)index {
    static NSString * EmptyIdentifier = @"EmptyIdentifier";
    static NSString * CellIdentifier = @"CellIdentifier";
    
    if ( index == emptyCellIndex )
    {
        NSLog( @"Loading empty cell at index %u", index );
        AQGridViewCell * hiddenCell = [gridView dequeueReusableCellWithIdentifier: EmptyIdentifier];
        if ( hiddenCell == nil )
        {
            // must be the SAME SIZE AS THE OTHERS
            // Yes, this is probably a bug. Sigh. Look at -[AQGridView fixCellsFromAnimation] to fix
            // (0.0, 0.0, 170.0, 130.0)
            hiddenCell = [[[AQGridViewCell alloc] initWithFrame: CGRectMake(0.0, 0.0, 157.0, 165.0) reuseIdentifier: EmptyIdentifier] autorelease];
        }
        
        hiddenCell.hidden = YES;
        return ( hiddenCell );
    }
    
    ProjectVideosGridViewCell * cell = (ProjectVideosGridViewCell *)[gridView dequeueReusableCellWithIdentifier: CellIdentifier];
    if ( cell == nil ) {
        // (0.0, 0.0, 170.0, 130.0)
        cell = [[[ProjectVideosGridViewCell alloc] initWithFrame:CGRectMake(0.0, 0.0, 157.0, 165.0) reuseIdentifier:CellIdentifier] autorelease];
    }
	
	// clear thumbnail if queued cell
    cell.thumbnailView.image = nil;
	
    cell.video = [videos objectAtIndex: index];
    
    return cell;
}

-(CGSize)portraitGridCellSizeForGridView:(AQGridView *)gridView {
    return ( CGSizeMake(192.0, 192.0) );
}

-(void)loadVideosFromService {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	VideosResultsBlock blk = ^(NSMutableArray *list, NSError *error) {
		appDelegate.videos = list;
        self.videos = list;
        [self.gridView reloadData];
		
		appDelegate.rootViewController.statusLabel.text = @"Received videos for projects";
		appDelegate.rootViewController.statusProgressView.progress = 1.0f;
		
		[UIView	 animateWithDuration:0.3 delay:0.5 options:UIViewAnimationOptionCurveLinear animations:^{
			appDelegate.rootViewController.statusView.alpha = 0.0f;
		} completion:^(BOOL finished){
			appDelegate.rootViewController.statusView.hidden = YES;
			appDelegate.rootViewController.statusView.alpha = 1.0f;
			appDelegate.rootViewController.statusProgressView.progress = 0.0f;
		}];
    };
	BasicBlock blk2 = ^{
		appDelegate.rootViewController.statusView.hidden = NO;
		appDelegate.rootViewController.statusLabel.text = @"Loading videos for project...";
	};
    [appDelegate.account videosForProject:project resultsBlock:blk startedBlock:blk2];
}

-(void)loadVideosFromServiceWithKey:(NSString *)key value:(NSString *)value {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	VideosResultsBlock blk = ^(NSMutableArray *list, NSError *error) {
		appDelegate.videos = list;
        self.videos = list;
        [self.gridView reloadData];
		
		appDelegate.rootViewController.statusLabel.text = @"Received videos for projects";
		appDelegate.rootViewController.statusProgressView.progress = 1.0f;
		
		[UIView	 animateWithDuration:0.3 delay:0.5 options:UIViewAnimationOptionCurveLinear animations:^{
			appDelegate.rootViewController.statusView.alpha = 0.0f;
		} completion:^(BOOL finished){
			appDelegate.rootViewController.statusView.hidden = YES;
			appDelegate.rootViewController.statusView.alpha = 1.0f;
			appDelegate.rootViewController.statusProgressView.progress = 0.0f;
		}];
    };
	BasicBlock blk2 = ^{
		appDelegate.rootViewController.statusView.hidden = NO;
		appDelegate.rootViewController.statusLabel.text = @"Loading videos for project...";
	};
    [appDelegate.account videosForProject:project resultsBlock:blk startedBlock:blk2 aleKey:key aleValue:value];
}

-(void)showMaterialsGridView {
    if (!materialsGridView) {
        materialsGridView = [[ProjectMaterialsGridView alloc] initWithFrame:gridView.frame];
        [materialsGridView loadProjectMaterials:project];
        [self.view insertSubview:materialsGridView.gridView aboveSubview:self.gridView];
    }
    materialsGridView.gridView.hidden = NO;
    gridView.hidden = YES;
}

-(void)showVideosGridView {
    materialsGridView.gridView.hidden =YES;
    gridView.hidden = NO;
}
-(IBAction)switchGridView:(id)sender {
    switch (self.segmentControl.selectedSegmentIndex) {
        case 0:
            [self showVideosGridView];
            break;
        case 1:
            [self showMaterialsGridView];
            break;
        default:
            break;
    }


}

#pragma mark -
#pragma mark UITextField delegate

- (BOOL)textFieldShouldBeginEditing:(UITextField *)textField {
    NSLog(@"Here text field key:%@",NSStringFromCGRect(filterSelectViewController.view.frame));
    
    if (!isShowingFilterList) {
        ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
        GetResultsBlock blk3 = ^(id results, NSError *error) {
            filterSelectViewController.keyList = results;
            [filterSelectViewController.keysTableView reloadData];
        };
        [appDelegate.account projectAleKeysForProject:project resultsBlock:blk3];
        [appDelegate.splitViewController.view addSubview:filterSelectViewController.view];
        isShowingFilterList = YES;
    } else {
        [filterSelectViewController.view removeFromSuperview];
        isShowingFilterList = NO;
    }
    
    return NO;
}

- (BOOL)textFieldShouldClear:(UITextField *)textField {
    NSLog(@"Clear button touched");
    aleKeySelectBox.text = nil;
    [self loadVideosFromService];
    return NO;
}


#pragma mark -
#pragma mark filterSelectViewController delegate
-(void)keyValuePairSelected:(NSString *)key value:(NSString *)value {
    aleKeySelectBox.text = [NSString stringWithFormat:@"%@ - %@", key, value];
    aleKeySelectBox.clearButtonMode = UITextFieldViewModeAlways;
    aleKeySelectBox.rightViewMode = UITextFieldViewModeNever;
    [filterSelectViewController.view removeFromSuperview];
    [self loadVideosFromServiceWithKey:key value:value];
}

@end
