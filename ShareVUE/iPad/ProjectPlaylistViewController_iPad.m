//
//  ProjectPlaylistViewController_iPad.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/23/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ProjectPlaylistViewController_iPad.h"
#import "ContentDetailViewController.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "ProjectVideosGridViewController.h"
#import "PlaylistListItemViewCell.h"
#import "AsyncUIImageView.h"
#import "VideoPlaybackListViewController_iPad.h"
#import <QuartzCore/QuartzCore.h>
#import "RootViewController.h"
#import "PlayPlaylistButton.h"
#import "VideoPlayFullViewController.h"
#import "VideoPlaybackCommentDelegate.h"
#import "CookieNavView.h"
#import "CreatePlaylistViewController.h"
#import "ProjectVideosGridViewController.h"


@implementation ProjectPlaylistViewController_iPad
@synthesize contentDetailViewController;
@synthesize popoverController;

- (void)dealloc {
	[videoFullViewController release];
	[popoverController release];
    [contentDetailViewController release];
    [super dealloc];
}

-(id)initWithStyle:(UITableViewStyle)style {
	if ((self = [super initWithStyle:style])) {
		tableView.rowHeight = 70;
		tableView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	}
	return self;
}

-(PlaylistListItemViewCell *)loadCellView {
	static NSString *kCellNibName = @"PlaylistTableViewCell";
	NSArray* topLevelObjects = [[NSBundle mainBundle] loadNibNamed:kCellNibName owner:nil options:nil];
	return [topLevelObjects objectAtIndex:0];
}

-(void)minScreen:(id)sender {
	[videoFullViewController.playbackDelegate pause:self];
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	UIWindow *window = appDelegate.window;
	NSArray *views = window.subviews;
	UIView *topView = [views objectAtIndex:0];
	[topView removeFromSuperview];
	[window addSubview:appDelegate.rootViewController.view];
	[videoFullViewController.playbackDelegate stop:self];
	[videoFullViewController release];
	videoFullViewController = nil;
	
}


-(void)startPlayingPlaylist:(id)sender {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	__block PlayPlaylistButton *playPlaylistButton = (PlayPlaylistButton *)sender;
	__block UIActivityIndicatorView *status = (UIActivityIndicatorView *)[playPlaylistButton.superview viewWithTag:1];
	status.hidden = NO;
	playPlaylistButton.hidden = YES;
	[status startAnimating];
	
	
	URLsResultsBlock blk = ^(NSArray *urls, NSError *error){
		playPlaylistButton.hidden = NO;
		status.hidden = YES;
		[status stopAnimating];
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
		videoFullViewController.playbackDelegate.mPlaybackView = (VideoPlaybackView *)[videoFullViewController.view viewWithTag:1];
		[videoFullViewController loadPlayerView];
        //videoFullViewController.playbackDelegate->durationHack = playPlaylistButton.playlist->duration;
		//videoFullViewController.video = [videos objectAtIndex:index];
		videoFullViewController.playbackDelegate.URLS = urls;
        
		
	};
	
	[appDelegate.account playlistUrls:playPlaylistButton.playlist resultsBlock:blk];
	
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)table cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"PlaylistTableViewCell";
    
    PlaylistListItemViewCell *cell = (PlaylistListItemViewCell *)[table dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {		
		//cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
		cell = [self loadCellView];
		[cell.playPlaylistButton addTarget:self action:@selector(startPlayingPlaylist:) forControlEvents:UIControlEventTouchUpInside];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
    }
    Playlist *pl = [playlists objectAtIndex:indexPath.row];
	cell.playPlaylistButton.playlist = pl;
    cell.title.text = pl.name;
    
    if (pl.createdDate) {
        cell.date.text = pl.createdDate;
    } else {
        cell.date.text = @"00/00/0000";
    }
    
	cell.thumbnail.layer.cornerRadius = 5.0;
	[cell.thumbnail imageViewFromURL:pl.thumbnailUrl];
	//cell.textLabel.textColor = [UIColor whiteColor];
    double dur = pl->duration;
     cell.durration.text = [NSString stringWithFormat:@"%02.0f:%02.0f", dur/60.0, fmodf(dur, 60)];
	//cell.detailTextLabel.text = pl.name;
	//cell.detailTextLabel.text = [NSString stringWithFormat:@"(%02.0f:%02.0f)",[pl.playlistItems count], dur/60.0, fmodf(dur, 60)];
	//cell.detailTextLabel.textColor = [UIColor lightGrayColor];
	
    //cell.imageView.image = [UIImage imageNamed:@"playlist.png"];
	cell.autoresizingMask = UIViewAutoresizingFlexibleWidth; 
    return cell;
}

#pragma mark -
#pragma mark View lifecycle

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
	self.view = [[UIView alloc] initWithFrame:CGRectZero];
	self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	self.view.autoresizesSubviews = YES;
	[self.view addSubview:tableView];
	

	if (UIInterfaceOrientationIsLandscape(self.interfaceOrientation)) {
		self.view.frame = CGRectMake(1024-368, 0, 320, 768);
	}
}

-(void)viewDidLoad{
	//ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	
	//NSString *myLabelText = @"Back To Projects"; 
	/*UIButton *backButton = [UIButton buttonWithType:UIButtonTypeCustom];
	
	// position in the parent view and set the size of the button
	backButton.frame = CGRectMake(0, 0, 120.0f, 40.0f);
	backButton.titleLabel.font =[UIFont fontWithName:@"Helvetica" size:14.0];
	backButton.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
	[backButton setTitleColor:UIColorFromRGB(0xff0e6fb9) forState:UIControlStateNormal];
	[backButton setTitleColor:[UIColor redColor] forState:UIControlStateSelected];
	[backButton setTitle:myLabelText forState:UIControlStateNormal];
	
	[backButton addTarget:self action:@selector(backtoProjects) forControlEvents:UIControlEventTouchUpInside];
	[appDelegate.rootViewController.backCookieTrailView addSubview:backButton];	
	*/
    /*
	CookieNav *cookie = [[CookieNav alloc] init];
	cookie.master = nil;
	cookie.detail = (UIViewController *)appDelegate.projectsGridViewController;
	
	[appDelegate.rootViewController.cookieNavView pushWithTitle:myLabelText cookie:cookie];
	*/
	[super viewDidLoad];
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration
{
	NSLog(@"Playlist view frame=====%@", NSStringFromCGRect(self.view.frame));
	if (UIInterfaceOrientationIsLandscape(toInterfaceOrientation)) {
		self.view.frame = CGRectMake(704, 0, 320, 768);
	} else {
		//self.view.frame = CGRectMake(0, 0, 768, 360);
	}
	
	if(toInterfaceOrientation == UIInterfaceOrientationPortrait || toInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
	{
		[projectName setFrame:CGRectMake(5, 9, 755, 30)];
		[titleWrapper setFrame:CGRectMake(7,5,755, 36)];
	}else {
		[projectName setFrame:CGRectMake(5, 9, 295, 30)];
		[titleWrapper setFrame:CGRectMake(7,5,307, 36)];
	}
}

#pragma mark -
#pragma mark Split view support

- (void)splitViewController: (MGSplitViewController *)svc willHideViewController:(UIViewController *)aViewController withBarButtonItem:(UIBarButtonItem*)barButtonItem forPopoverController: (UIPopoverController*)pc {
    /*
    barButtonItem.title = @"Projects";
    NSMutableArray *items = [[toolbar items] mutableCopy];
    [items insertObject:barButtonItem atIndex:0];
    [toolbar setItems:items animated:YES];
    [items release];
    self.popoverController = pc;*/
}

// Called when the view is shown again in the split view, invalidating the button and popover controller.
- (void)splitViewController: (MGSplitViewController *)svc willShowViewController:(UIViewController *)aViewController invalidatingBarButtonItem:(UIBarButtonItem *)barButtonItem {
    /*
    NSMutableArray *items = [[toolbar items] mutableCopy];
    [items removeObjectAtIndex:0];
    [toolbar setItems:items animated:YES];
    [items release];
    self.popoverController = nil;
	 */
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	NSString *myLabelText = @"<  Back To Project Details"; 
    CookieNav *cookie = [[CookieNav alloc] init];
	cookie.master = self;
    ContentDetailViewController *cdetail = (ContentDetailViewController *)appDelegate.splitViewController.detailViewController;
	cookie.detail = cdetail.contentController;
     cookie.masterBeforeDetail = NO;
    [appDelegate.rootViewController.cookieNavView pushWithTitle:myLabelText cookie:cookie];
    
	[tableView deselectRowAtIndexPath:indexPath animated:NO];
	
	//dispatch_async(dispatch_get_main_queue(), ^{
		
		//dispatch_async(dispatch_get_main_queue(), ^{
            
			//[appDelegate.splitViewController toggleMasterView:self];
			VideoPlaybackListViewController_iPad *controller = [[VideoPlaybackListViewController_iPad alloc] initWithStyle:UITableViewStylePlain];
			controller.playlist = [playlists objectAtIndex:indexPath.row];
			controller.contentDetailViewController = self.contentDetailViewController;
    cookie.delegate = controller;
			appDelegate.splitViewController.masterViewController = controller;
			appDelegate.splitViewController.detailViewController.view.frame = CGRectMake(0, 0, 600, 1024);
            [appDelegate.splitViewController toggleMasterBeforeDetail:self];
			//[controller release];
			//dispatch_async(dispatch_get_main_queue(), ^{
				//appDelegate.splitViewController.masterBeforeDetail = YES;
				//dispatch_async(dispatch_get_main_queue(), ^{ 
					//[appDelegate.splitViewController toggleMasterView:self];
				//});
			//});
		//});
	//});
	
	//ProjectVideosGridViewController *controller = (ProjectVideosGridViewController *)contentDetailViewController.contentController;
	//Playlist *playlist = [playlists	objectAtIndex:indexPath.row];
	//controller.videos = playlist.videos;
	//[controller.gridView reloadData];
	[cookie release];
}

-(void)addPlaylist:(id)sender {
	
	// Create the modal view controller
	CreatePlaylistViewController *viewController = [[CreatePlaylistViewController alloc] initWithNibName:@"CreatePlaylistViewController" bundle:nil];
	viewController.delegate = self;
	viewController.project  = project;
	ProjectVideosGridViewController *videoGridView = (ProjectVideosGridViewController *)contentDetailViewController.contentController;
	viewController.videos = videoGridView.videos;
	// Create a Navigation controller
	//UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:viewController];
	//navController.modalPresentationStyle = UIModalPresentationFormSheet;
	//[navController.navigationBar setBarStyle:UIBarStyleBlack];
	
	// show the navigation controller modally
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	viewController.modalPresentationStyle = UIModalPresentationFullScreen;
	[appDelegate.rootViewController presentModalViewController:viewController animated:YES];
	
	// Clean up resources
	//[navController release];
	[viewController release];
	
}
-(void)doneSavingPlaylist:(Playlist *)playlist {
	[playlists insertObject:playlist atIndex:0];
	[self.tableView reloadData];
}

@end
