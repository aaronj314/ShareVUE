    //
//  CreatePlaylistViewController.m
//  ShareVUE
//
//  Created by Darren Mason on 2/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CreatePlaylistViewController.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "RootViewController.h"
#import "CreatePlaylistVideoGridViewCell.h"
#import <QuartzCore/QuartzCore.h>
#import "AsyncUIImageView.h"
#import "VideoListItemViewCell.h"

@implementation CreatePlaylistViewController
@synthesize titlePanel;
@synthesize delegate;
@synthesize project;
@synthesize gridView;
@synthesize videos;
@synthesize playlistItems;
@synthesize playlistName;
@synthesize tableView;
@synthesize playlist;

- (void)dealloc {
	[playlist release];
	[playlistName release];
	[playlistItems release];
	[tableView release];
	[videos release];
	[gridView release];
	[project release];
	[delegate release];
	[titlePanel release];
    [super dealloc];
}

 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization.
		playlistItems = [[NSMutableArray alloc] initWithCapacity:0];
    }
    return self;
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	[super viewDidLoad];
	
	if (editing) {
		playlistName.text = playlist.name;
		shared.on = playlist->sharing;
		self.playlistItems = playlist.playlistItems;
	}
	
	self.view.backgroundColor = UIColorFromRGB(0xff3d3d3d);//rgb 61,61,61
	tableView.separatorColor = [UIColor blackColor];
	tableView.layer.cornerRadius = 5.0f;
	titlePanel.layer.cornerRadius =10.0f;
	tableView.rowHeight = 70;
	tableView.editing = YES;
	emptyCellIndex = NSNotFound;
    
    //self.view.autoresizesSubviews = YES;
    // background goes in first
    //UIImageView * background = [[UIImageView alloc] initWithFrame: self.view.bounds];
    //background.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
    //background.contentMode = UIViewContentModeCenter;
    //background.image = [UIImage imageNamed: @"background.png"];
    
    //[self.view addSubview: background];
    
    // grid view sits on top of the background image
    //gridView = [[AQGridView alloc] initWithFrame: self.view.bounds];
    //gridView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
    //gridView.opaque = NO;
    gridView.dataSource = self;
    gridView.delegate = self;
    gridView.scrollEnabled = YES;
	gridView.layer.cornerRadius = 5.0;
	gridView.contentInset = UIEdgeInsetsMake(10, 0, 10, 0);
    
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


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    //return YES;
	return ((interfaceOrientation == UIInterfaceOrientationLandscapeLeft) || (interfaceOrientation == UIInterfaceOrientationLandscapeRight));
}



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

-(IBAction)savePlaylist:(id)sender {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	if ([playlistName.text isEqual:@""] || playlistName.text == nil) {
		[appDelegate.rootViewController dismissModalViewControllerAnimated:YES];
		return;
	}
	
	if (editing) {
		CreateResultsBlock blk = ^(id result, NSError *error) {
			[delegate doneSavingPlaylist:result];
			[appDelegate.rootViewController dismissModalViewControllerAnimated:YES];
		};
		playlist->sharing = shared.on;
		playlist.name = playlistName.text;
		playlist.playlistItems = playlistItems;
		[appDelegate.account updatePlaylist:playlist resultsBlock:blk];
	} else {
		CreateResultsBlock blk = ^(id result, NSError *error) {
			[delegate doneSavingPlaylist:result];
			[appDelegate.rootViewController dismissModalViewControllerAnimated:YES];
		};
		Playlist *pl = [[Playlist alloc] init];
		pl->sharing = shared.on;
		pl.name = playlistName.text;
		pl.playlistItems = playlistItems;
		[appDelegate.account createPlaylist:pl project:project resultsBlock:blk];
    }
		
}

-(IBAction)cancel:(id)sender {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    
    if ([delegate respondsToSelector:@selector(cancelSavingPlaylist)]) {
         [delegate cancelSavingPlaylist];
    }
    
	[appDelegate.rootViewController dismissModalViewControllerAnimated:YES];
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
	//NSLog(@"Selection");
	///ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	PlaylistItem *pi = [[PlaylistItem alloc] initWithVideo:[videos objectAtIndex:index]]; 
	[playlistItems addObject:pi];
	[self.tableView reloadData];
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
            draggingCell = [[CreatePlaylistVideoGridViewCell alloc] initWithFrame: frame reuseIdentifier: @""];
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
            hiddenCell = [[[AQGridViewCell alloc] initWithFrame: CGRectMake(0.0, 0.0, 96, 124.0) reuseIdentifier: EmptyIdentifier] autorelease];
        }
        
        hiddenCell.hidden = YES;
        return ( hiddenCell );
    }
    
    CreatePlaylistVideoGridViewCell * cell = (CreatePlaylistVideoGridViewCell *)[gridView dequeueReusableCellWithIdentifier: CellIdentifier];
    if ( cell == nil )
    {
        cell = [[[CreatePlaylistVideoGridViewCell alloc] initWithFrame:CGRectMake(0.0, 0.0, 96, 124.0) reuseIdentifier:CellIdentifier] autorelease];
    }
	
	// clear thumbnail if queued cell
    cell.thumbnailView.image = nil;
	
    cell.video = [videos objectAtIndex: index];
    
    return cell;
}

-(CGSize)portraitGridCellSizeForGridView:(AQGridView *)gridView {
    return ( CGSizeMake(96, 124.0) );
}


#pragma mark -
#pragma mark Table view data source

// Customize the number of sections in the table view.
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    return 1;
}

/*
- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
	return @"base section";
}
*/

// Customize the number of rows in the table view.
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [playlistItems count];
}


-(VideoListItemViewCell *)loadCellView {
	static NSString *kCellNibName = @"VideoListItemView";
	NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:nil options:nil];
	return [topLevelObjects objectAtIndex:0];
}

// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)table cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	
	static NSString *CellIdentifier = @"VideoListItemView";
    
    VideoListItemViewCell *cell = (VideoListItemViewCell *)[table dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {		
        cell = [self loadCellView];
		//cell.contentView.backgroundColor = UIColorFromRGB(0xff3d3d3d);//rgb 61,61,61
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
    }
    PlaylistItem *pl = [playlistItems objectAtIndex:indexPath.row];
    cell.title.text = pl.videoName;
	cell.thumbnail.layer.cornerRadius = 5.0;
	[cell.thumbnail imageViewFromURL:pl.thumbnailUrl];
	//cell.textLabel.textColor = [UIColor whiteColor];
    double dur = pl->duration;
	//cell.detailTextLabel.text = [NSString stringWithFormat:@"(%02.0f:%02.0f)",[pl.playlistItems count], dur/60.0, fmodf(dur, 60)];
	//cell.detailTextLabel.textColor = [UIColor lightGrayColor];
	
    //cell.imageView.image = [UIImage imageNamed:@"playlist.png"];
	
    return cell;
	
}

/*
 // Override to support conditional editing of the table view.
 - (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the specified item to be editable.
 return YES;
 }
 */



 // Override to support editing the table view.
 - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
 
	 if (editingStyle == UITableViewCellEditingStyleDelete) {
		 // Delete the row from the data source.
		 [playlistItems removeObjectAtIndex:indexPath.row];
		 [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
	 }   
   
 }
 

-(UITableViewCellEditingStyle)tableView:(UITableView *)tableView editingStyleForRowAtIndexPath:(NSIndexPath *)indexPath {
	return UITableViewCellEditingStyleDelete;
}


 // Override to support rearranging the table view.
 - (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath {
	 [playlistItems exchangeObjectAtIndex:fromIndexPath.row withObjectAtIndex:toIndexPath.row];
 }
 



 // Override to support conditional rearranging of the table view.
 - (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath {
 // Return NO if you do not want the item to be re-orderable.
 return YES;
 }
 


#pragma mark -
#pragma mark Table view delegate

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
}

-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath {
	
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

@end
