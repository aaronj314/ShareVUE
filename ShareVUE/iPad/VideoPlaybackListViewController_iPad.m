    //
//  VideoPlaybackListViewController.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "VideoPlaybackListViewController_iPad.h"
#import "VideoListItemViewCell.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "AsyncUIImageView.h"
#import <QuartzCore/QuartzCore.h>
#import "RootViewController.h"
#import "ContentDetailViewController.h"
#import "VideoPlayViewController.h"
#import "VideoPlaybackCommentDelegate.h"
#import "CookieNavView.h"
#import "CookieNav.h"
#import "CreatePlaylistViewController.h"
#import "ProjectVideosGridViewController.h"

@implementation VideoPlaybackListViewController_iPad

@synthesize contentDetailViewController;
@synthesize popoverController;
@synthesize videoPlayViewController;

- (void)dealloc {
	[videoPlayViewController release];
	[popoverController release];
    [contentDetailViewController release];
    [super dealloc];
}

#define UIColorFromRGB(rgbValue) [UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0xFF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

-(id)initWithStyle:(UITableViewStyle)style {
	if ((self = [super initWithStyle:style])) {
		self.contentSizeForViewInPopover = CGSizeMake(320.0, 600.0);
		tableView.rowHeight = 70;
	}
	return self;
}

-(void)editPlaylist:(id)sender {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    
    [videoPlayViewController.playbackDelegate pause:self];
    
	// Create the modal view controller
	CreatePlaylistViewController *viewController = [[CreatePlaylistViewController alloc] initWithNibName:@"CreatePlaylistViewController" bundle:nil];
	viewController.delegate = self;
	viewController.project  = project;
	viewController.playlist = playlist;
	viewController->editing = YES;
	viewController.videos = appDelegate.videos;
	// Create a Navigation controller
	//UINavigationController *navController = [[UINavigationController alloc] initWithRootViewController:viewController];
	//navController.modalPresentationStyle = UIModalPresentationFormSheet;
	//[navController.navigationBar setBarStyle:UIBarStyleBlack];
	
	// show the navigation controller modally
	viewController.modalPresentationStyle = UIModalPresentationFullScreen;
	[appDelegate.rootViewController presentModalViewController:viewController animated:YES];
	
	// Clean up resources
	//[navController release];
	[viewController release];
	
}

-(void)doneSavingPlaylist:(Playlist *)pl {
    [videoPlayViewController.playbackDelegate play:self];
	self.playlist = pl;
    playlistName.text = pl.name;
	[self.tableView reloadData];
}

-(void)cancelSavingPlaylist {
    [videoPlayViewController.playbackDelegate play:self];
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


// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
    [super loadView];
	self.view = [[UIView alloc] initWithFrame:CGRectZero];
	self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	[self.view addSubview:tableView];
	playlistName.text = playlist.name;
	playlistItems = playlist.playlistItems;
	[self.view addSubview:titleWrapper];
}



// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
	
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();

	//NSString *myLabelText = @"<  Back To Project Details"; 
    /*
	UIButton *backButton = [UIButton buttonWithType:UIButtonTypeCustom];
	
	// position in the parent view and set the size of the button
	backButton.frame = CGRectMake(105, 0, 200.0f, 40.0f);
	backButton.titleLabel.font =[UIFont fontWithName:@"Helvetica" size:14.0];
	backButton.contentVerticalAlignment = UIControlContentVerticalAlignmentCenter;
	[backButton setTitleColor:UIColorFromRGB(0xff0e6fb9) forState:UIControlStateNormal];
	[backButton setTitleColor:[UIColor redColor] forState:UIControlStateSelected];
	[backButton setTitle:myLabelText forState:UIControlStateNormal];
	
	[backButton addTarget:self action:@selector(backtoProjectsDetails) forControlEvents:UIControlEventTouchUpInside];
	
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

- (void)viewDidAppear:(BOOL)animated {
	//[super viewDidAppear:animated];
	//[self.tableView reloadData];
    if ([playlistItems count] > 0) {
        NSIndexPath *idxPath = [NSIndexPath indexPathForRow:0 inSection:0];
        [self.tableView selectRowAtIndexPath:idxPath animated:NO scrollPosition:UITableViewScrollPositionTop];
        [self tableView:self.tableView didSelectRowAtIndexPath:idxPath];
    } else {
        // this is bad but no time to fix
        VideoPlayViewController *vidPlayViewVC = [[VideoPlayViewController alloc] initWithNibName:@"VideoPlayViewController" bundle:nil];
        self.videoPlayViewController = vidPlayViewVC;
        [vidPlayViewVC release];
        videoPlayViewController.view;
        [self.contentDetailViewController setDetailItem:videoPlayViewController];
        
        //PlaylistItem *pi = [playlistItems objectAtIndex:indexPath.row];
        //SourceVideo *v = pi.video;
        //[self.contentViewController addTitle:v.name];
        //self.videoPlayViewController.video = v;
        //hack for issues with AVAsset duration in 4.3
        //self.videoPlayViewController.playbackDelegate->durationHack = 60.0;//v->duration;
        [self.videoPlayViewController.tableView reloadData];
        //[self fetchSourceVideo:v];
        //[self.videoPlayViewController.playbackDelegate showLoadingAlertView];
    }
	
}

-(void)backtoProjectsDetails{
	NSLog(@"Back to details");
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
    if (pl.createdDate) {
        cell.date.text = pl.createdDate;
    } else {
        cell.date.text = @"00/00/0000";
    }
    
	cell.thumbnail.layer.cornerRadius = 5.0;
    cell.commentCount.text = [NSString stringWithFormat:@"Comment ( %i )", pl->numComments];
	[cell.thumbnail imageViewFromURL:pl.thumbnailUrl];
	//cell.textLabel.textColor = [UIColor whiteColor];
    double dur = pl->duration;
    cell.durration.text = [NSString stringWithFormat:@"%02.0f:%02.0f", dur/60.0, fmodf(dur, 60)];
	//cell.detailTextLabel.text = [NSString stringWithFormat:@"(%02.0f:%02.0f)",[pl.playlistItems count], dur/60.0, fmodf(dur, 60)];
	//cell.detailTextLabel.textColor = [UIColor lightGrayColor];
	
    //cell.imageView.image = [UIImage imageNamed:@"playlist.png"];
	
    return cell;
	
}

-(void)fetchSourceVideo:(SourceVideo *)v {
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	VideoURLResultsBlock blk = ^(NSURL *url, NSError *error){
        //NSURL *t = [NSURL URLWithString:@"http://devimages.apple.com/iphone/samples/bipbop/bipbopall.m3u8"];
		self.videoPlayViewController.playbackDelegate.URL = url;
		
	};
	
	CommentsResultsBlock blk2 = ^(NSMutableArray *comments, NSError *error){
		[self.videoPlayViewController.tableView reloadData];
	};
    
    GetResultsBlock blk3 = ^(id object, NSError *error){
    
    };
	
	//[appDelegate.tcnAccount videosUrls:v resultsBlock:blk];
	//[appDelegate.account videoUrl:v preset:nil resulsBlock:blk];
    [appDelegate.account videoHttpLiveUrl:v resulsBlock:blk];
	[appDelegate.account commentsForVideo:v resultsBlock:blk2];
    
    [appDelegate.account getVideoALE:v resultsBlock:blk3];
}
 
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	VideoPlayViewController *vidPlayViewVC = [[VideoPlayViewController alloc] initWithNibName:@"VideoPlayViewController" bundle:nil];
	self.videoPlayViewController = vidPlayViewVC;
	[vidPlayViewVC release];
	videoPlayViewController.view;
	[self.contentDetailViewController setDetailItem:videoPlayViewController];
	
	PlaylistItem *pi = [playlistItems objectAtIndex:indexPath.row];
	SourceVideo *v = pi.video;
	//[self.contentViewController addTitle:v.name];
	self.videoPlayViewController.video = v;
    //hack for issues with AVAsset duration in 4.3
	//self.videoPlayViewController.playbackDelegate->durationHack = 60.0;//v->duration;
	[self.videoPlayViewController.tableView reloadData];
	[self fetchSourceVideo:v];
	[self.videoPlayViewController.playbackDelegate showLoadingAlertView];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    return YES;
}

- (void)willRotateToInterfaceOrientation:(UIInterfaceOrientation)toInterfaceOrientation duration:(NSTimeInterval)duration{

	if(toInterfaceOrientation == UIInterfaceOrientationPortrait || toInterfaceOrientation == UIInterfaceOrientationPortraitUpsideDown)
	{
		[playlistName setFrame:CGRectMake(5, 5, 755, 30)];
		[titleWrapper setFrame:CGRectMake(7,5,755, 36)];
	}else {
		[playlistName setFrame:CGRectMake(5, 5, 295, 30)];
		[titleWrapper setFrame:CGRectMake(7,5,307, 36)];
	}

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

#pragma mark -
#pragma mark CookieNav pop delegate
-(void)navPop {
    //NSLog(@"NavPop called");
    [videoPlayViewController.playbackDelegate stop:self];
}
@end
