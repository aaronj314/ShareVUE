    //
//  ProjectMaterialsGridViewController.m
//  ShareVUE
//
//  Created by Aaron Jones on 3/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ProjectMaterialsGridViewController.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "SignInViewController.h";
#import "ProjectPlaylistViewController_iPad.h"
#import "ProjectVideosGridViewController.h"
#import "ContentDetailViewController.h"
#import "MGSplitViewController.h"
#import "RootViewController.h"
#import "CookieNavView.h"
#import "DocumentGridViewCell.h"

@implementation ProjectMaterialsGridViewController
@synthesize project;
@synthesize projectName;
@synthesize materials;
@synthesize segmentControl;
@synthesize gridView;
@synthesize contentDetailViewController;

- (void)dealloc
{
	[materials release];
    [contentDetailViewController release];
	[projectName release];
    [project release];
    [gridView release];
    [segmentControl release];
    [super dealloc];
}

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

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
    
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
	
}


- (void)viewDidUnload
{
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
        //NSLog( @"Setting left+right content insets to zero" );
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

- (void) gridView: (AQGridView *) gridView didSelectItemAtIndex: (NSUInteger) index {
	NSLog(@"Selection");
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    
    
    PlaylistsResultsBlock blk = ^(NSMutableArray *list, NSError *error) {
        // set back to projects grid nav link
        NSString *myLabelText = @"Back To Projects";
        CookieNav *cookie = [[CookieNav alloc] init];
        cookie.main = self;
        [appDelegate.rootViewController.cookieNavView pushWithTitle:myLabelText cookie:cookie];
        
		[gridView deselectItemAtIndex:index animated:NO];
		ProjectPlaylistViewController_iPad *controller = [[ProjectPlaylistViewController_iPad alloc] initWithStyle:UITableViewStylePlain];
        controller.contentDetailViewController = appDelegate.contentDetailViewController;
		controller.playlists = list;
		controller.project = [materials objectAtIndex:index];
		appDelegate.splitViewController.masterBeforeDetail = NO;
		appDelegate.splitViewController.viewControllers = [NSArray arrayWithObjects:controller,appDelegate.contentDetailViewController, nil];
		appDelegate.splitViewController.dividerStyle = MGSplitViewDividerStyleThin;
		;
		appDelegate.splitViewController.splitWidth = 1.0f;
		if (!appDelegate.splitViewController.isLandscape) {
			appDelegate.splitViewController.vertical = NO;
		}
		//appDelegate.splitViewController.viewControllers = [NSArray arrayWithObjects:test,appDelegate.contentDetailViewController, nil];
		//[controller release];
		/*
		 [UIView animateWithDuration:0.3 animations:^{
		 self.view.alpha = 0.0;
		 }];
		 */
        ProjectVideosGridViewController *projectVideosGridViewController = [[ProjectVideosGridViewController alloc] initWithNibName:@"ProjectVideosGridViewController" bundle:nil];
        projectVideosGridViewController.project = [materials objectAtIndex:index];
		projectVideosGridViewController.contentDetailViewController = appDelegate.contentDetailViewController;
        [controller.contentDetailViewController setDetailItem:projectVideosGridViewController];
        [projectVideosGridViewController loadVideosFromService];
        
		appDelegate.rootViewController.mainViewController = appDelegate.splitViewController;
	};
	[appDelegate.account playlistForProject:[materials objectAtIndex:index] resultsBlock:blk];
	
    /*
	 VideosResultsBlock blk3 = ^(NSMutableArray *list, NSError *error) {
	 //ProjectVideosGridView *projectVideosGrid = [[ProjectVideosGridView alloc] initWithNibName:@"ProjectVideosGridView" bundle:nil];
	 //projectVideosGrid.videos = list;
	 //[projectVideosGrid.gridView reloadData];
	 //[[appDelegate.splitViewController.viewControllers objectAtIndex:1]  setDetailItem:projectVideosGrid];
	 };
	 [appDelegate.account videosForProject:[projects objectAtIndex:index] resultsBlock:blk3];
     */
	
	
}


- (BOOL) gestureRecognizerShouldBegin: (UIGestureRecognizer *) gestureRecognizer
{
    CGPoint location = [gestureRecognizer locationInView: gridView];
    if ( [gridView indexForItemAtPoint: location] < [materials count] )
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
				index = [materials count] - 1;
			}
            
            // update the data store
            id obj = [[materials objectAtIndex: dragOriginIndex] retain];
            [materials removeObjectAtIndex: dragOriginIndex];
            [materials insertObject: obj atIndex: index];
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
            draggingCell = [[DocumentGridViewCell alloc] initWithFrame: frame reuseIdentifier: @""];
            draggingCell.iconView = [materials objectAtIndex: index];
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
				index = [materials count] - 1;
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
    return ( [materials count] );
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
            hiddenCell = [[[AQGridViewCell alloc] initWithFrame: CGRectMake(0.0, 0.0, 170.0, 179.0) reuseIdentifier: EmptyIdentifier] autorelease];
        }
        
        hiddenCell.hidden = YES;
        return ( hiddenCell );
    }
    
    DocumentGridViewCell * cell = (DocumentGridViewCell *)[gridView dequeueReusableCellWithIdentifier: CellIdentifier];
    if ( cell == nil )
    {
        cell = [[[DocumentGridViewCell alloc] initWithFrame:CGRectMake(0.0, 0.0, 170.0, 179.0) reuseIdentifier:CellIdentifier] autorelease];
    }
    
    cell.project = [materials objectAtIndex: index];
    
    return cell;
}

-(CGSize)portraitGridCellSizeForGridView:(AQGridView *)gridView {
    return ( CGSizeMake(192.0, 192.0) );
}


@end
