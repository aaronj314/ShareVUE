    //
//  VideoPlaybackListViewController.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/25/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "VideoPlaybackListViewController.h"
#import "ShareVUEAppDelegate.h"
#import <QuartzCore/QuartzCore.h>

@implementation VideoPlaybackListViewController
@synthesize playlistItems;
@synthesize playlist;
@synthesize project;

- (void)dealloc {
	[titleWrapper release];
	[playlistName release];
	[playlistItems release];
	[playlist release];
	[project release];
    [super dealloc];
}


#define UIColorFromRGB(rgbValue) [UIColor \
colorWithRed:((float)((rgbValue & 0xFF0000) >> 16))/255.0 \
green:((float)((rgbValue & 0xFF00) >> 8))/255.0 \
blue:((float)(rgbValue & 0xFF))/255.0 alpha:1.0]

-(id)initWithStyle:(UITableViewStyle)style {
	if ((self = [super initWithStyle:style])) {
		self.title = @"Playlist Videos";
		
		
		UIButton *addButton = [UIButton buttonWithType:UIButtonTypeCustom];
		
		[addButton addTarget:self action:@selector(editPlaylist:) forControlEvents:UIControlEventTouchUpInside];
		
		// position in the parent view and set the size of the button
		addButton.frame = CGRectMake(5, 7, 26.0f, 25.0f);
		
		UIImage *image = [UIImage imageNamed:@"editplaylist.png"];
		
		[addButton setBackgroundImage:image forState:UIControlStateNormal];
		
		playlistName = [[UITextField alloc] initWithFrame:CGRectMake(5, 7, 755, 30)];
		playlistName.text = @"Project Title Goes Here";
		playlistName.textColor = [UIColor whiteColor];
		playlistName.userInteractionEnabled = NO;
		playlistName.textAlignment = UITextAlignmentCenter;
		UIFont* boldFont = [UIFont boldSystemFontOfSize:18.0];
		playlistName.font = boldFont;
		
		titleWrapper = [[UIView alloc] initWithFrame:CGRectMake(7,5,755, 36)];//307,36
		titleWrapper.backgroundColor = UIColorFromRGB(0xff636363);
		titleWrapper.layer.cornerRadius =10.0;
		
		if (UIInterfaceOrientationIsLandscape(self.interfaceOrientation)) {
			[playlistName setFrame:CGRectMake(31, 9, 260, 30)];
			[titleWrapper setFrame:CGRectMake(7,5,307, 36)];
		}
		
		[titleWrapper addSubview:addButton];
		[titleWrapper addSubview:playlistName];
		 
		
		CGRect listFrame = CGRectMake(0, 45, tableView.frame.size.width, tableView.frame.size.height);
		tableView.frame = listFrame;
		tableView.backgroundColor = UIColorFromRGB(0xff3d3d3d);//rgb 61,61,61
		tableView.separatorColor = [UIColor blackColor];
		tableView.separatorStyle = UITableViewCellSeparatorStyleNone;
	
	}
	
	return self;
}

-(void)editPlaylist:(id)sender {


}

#pragma mark -
#pragma mark Initialization

/*
 - (id)initWithStyle:(UITableViewStyle)style {
 // Override initWithStyle: if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
 self = [super initWithStyle:style];
 if (self) {
 // Custom initialization.
 }
 return self;
 }
 */


#pragma mark -
#pragma mark View lifecycle

// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
	[super loadView];
}

/*
 - (void)viewDidLoad {
 [super viewDidLoad];
 
 // Uncomment the following line to preserve selection between presentations.
 // self.clearsSelectionOnViewWillAppear = NO;
 
 // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
 // self.navigationItem.rightBarButtonItem = self.editButtonItem;
 }
 */

-(void) viewWillAppear:(BOOL)animated {
	[super viewWillAppear:animated];
}


 - (void)viewDidAppear:(BOOL)animated {
	 [super viewDidAppear:animated];
	 [self.tableView reloadData];
	 NSIndexPath *idxPath = [NSIndexPath indexPathForRow:0 inSection:0];
	 //[self.tableView selectRowAtIndexPath:idxPath animated:NO scrollPosition:UITableViewScrollPositionNone];
	 [self tableView:self.tableView didSelectRowAtIndexPath:idxPath];
 }
 
/*
 - (void)viewWillDisappear:(BOOL)animated {
 [super viewWillDisappear:animated];
 }
 */
/*
 - (void)viewDidDisappear:(BOOL)animated {
 [super viewDidDisappear:animated];
 }
 */


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Override to allow orientations other than the default portrait orientation.
    return YES;
}


#pragma mark -
#pragma mark Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {
    // Return the number of sections.
    return 1;
}

- (NSString *)tableView:(UITableView *)tableView titleForHeaderInSection:(NSInteger)section {
	return nil;
}



- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    // Return the number of rows in the section.
    return [playlistItems count];
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)table cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    static NSString *CellIdentifier = @"VideoPlaybackListCell";
    
    UITableViewCell *cell = [table dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) {
        cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleSubtitle reuseIdentifier:CellIdentifier] autorelease];
        cell.selectionStyle = UITableViewCellSelectionStyleGray;
    }
    PlaylistItem *pl = [playlistItems objectAtIndex:indexPath.row];
    cell.textLabel.text = pl.videoName;
    //double dur = pl->duration;
	//cell.detailTextLabel.text = [NSString stringWithFormat:@"%i videos (%02.0f:%02.0f)",[pl.playlistItems count], dur/60.0, fmodf(dur, 60)];
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


/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)table commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
}
*/


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

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
	
	/*PlaylistDetailViewController *controller = [[PlaylistDetailViewController alloc] initWithNibName:@"PlaylistDetailViewController" bundle:nil];
	 
	 controller.playlist  = [playlists objectAtIndex:indexPath.row];
	 Playlist *pl = [playlists objectAtIndex:indexPath.row];
	 NSLog(@"Playlist NAME: %@",pl.name);
	 [self.navigationController pushViewController:controller animated:YES];
	 [controller release];*/
}

-(void)addPlaylist:(id)sender {
	/*
	 TechnicolorDailiesAppDelegate *appDelegate = (TechnicolorDailiesAppDelegate *)[UIApplication sharedApplication].delegate;
	 TCNCreateResultsBlock blk = ^(id project, NSError *error) {
	 [self.playlists addObject:project];
	 [self.tableView reloadData];
	 };
	 [appDelegate.tcnAccount createPlaylistWithName:@"test from iPad 2" resultsBlock:blk];
	 */
	/*
	 Playlist *playlist =[[Playlist alloc] init];
	 playlist.name = @"New Playlist";
	 [playlists insertObject:playlist atIndex:0];
	 [self.tableView reloadData];
	 [playlist release];
	 */
	
}

#pragma mark -
#pragma mark Memory management

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Relinquish ownership any cached data, images, etc. that aren't in use.
}

- (void)viewDidUnload {
    // Relinquish ownership of anything that can be recreated in viewDidLoad or on demand.
    // For example: self.myOutlet = nil;
}

@end
