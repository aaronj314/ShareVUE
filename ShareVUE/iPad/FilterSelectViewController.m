//
//  FilterSelectViewController.m
//  ShareVUE
//
//  Created by Aaron Jones on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "FilterSelectViewController.h"
#import "ShareVUEAppDelegate_iPad.h"
#import <QuartzCore/QuartzCore.h>

static NSUInteger keyIdx;
static NSUInteger valueIdx;

@implementation FilterSelectViewController
@synthesize delegate;
@synthesize keysTableView;
@synthesize valuesTableView;
@synthesize keyList;
@synthesize valueList;
@synthesize project;

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        
        background = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"filter-bg.png"]];
        // Custom initialization
        keysTableView = [[UITableView alloc] initWithFrame:CGRectMake(10,30,255, 350) style:UITableViewStylePlain];
        //keysTableView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        keysTableView.delegate = self;
        keysTableView.dataSource = self;
        keysTableView.rowHeight = 35;
        
        
        valuesTableView = [[UITableView alloc] initWithFrame:CGRectMake(10,30,255, 350) style:UITableViewStylePlain];
        //keysTableView.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
        valuesTableView.delegate = self;
        valuesTableView.dataSource = self;
        valuesTableView.rowHeight = 35;
        //self.view.backgroundColor = [UIColor darkGrayColor];
        
    }
    return self;
}

- (void)dealloc {
    [delegate release];
    [keysTableView release];
    [valuesTableView release];
    [keyList release];
    [valueList release];
    [project release];
    [background release];
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView
{
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    //self.view.layer.cornerRadius = 5.0;
    self.view.backgroundColor = [UIColor clearColor];
    keysTableView.layer.cornerRadius = 5.0;
    valuesTableView.layer.cornerRadius = 5.0;
    [self.view addSubview:background];
    [self.view addSubview:valuesTableView];
    [self.view addSubview:keysTableView];
}


- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
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
    if (tableView == keysTableView) {
        return [keyList count];
    } else if (tableView == valuesTableView) {
        return ([valueList count] > 0 ? ([valueList count] + 1) : 0);
    } else {
        return 0;
    }
}


// Customize the appearance of table view cells.
- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
	UITableViewCell *cell = nil;
    
	static NSString *kDisplayCell_ID = @"ProjectDetailDisplayCellID";
	cell = [tableView dequeueReusableCellWithIdentifier:kDisplayCell_ID];
	if (cell == nil) {
		cell = [[[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:kDisplayCell_ID] autorelease];
		cell.selectionStyle = UITableViewCellSelectionStyleGray;
        cell.textLabel.font = [UIFont fontWithName:@"Helvetica" size:12];
	}
    
    if (tableView == keysTableView) {
        cell.textLabel.text = [keyList objectAtIndex:indexPath.row];
        cell.accessoryType = UITableViewCellAccessoryDisclosureIndicator;
    } else if (tableView == valuesTableView) {
        if (indexPath.row == [valueList count]) {
            cell.textLabel.text = @"<< back to keys";
            cell.textLabel.font = [UIFont fontWithName:@"Helvetica-Bold" size:12];
        } else {
            cell.textLabel.text = [valueList objectAtIndex:indexPath.row];
        }
        cell.accessoryType = UITableViewCellAccessoryNone;
    }
    
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
 - (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
 
 if (editingStyle == UITableViewCellEditingStyleDelete) {
 // Delete the row from the data source.
 [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
 }   
 else if (editingStyle == UITableViewCellEditingStyleInsert) {
 // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view.
 }   
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

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    
    if (tableView == keysTableView) {
        keyIdx = indexPath.row;
        GetResultsBlock blk3 = ^(id results, NSError *error) {
            self.valueList = results;
            keysTableView.hidden = YES;
            [valuesTableView reloadData];
        };
        [appDelegate.account projectAleValuesForProject:project key:[keyList objectAtIndex:indexPath.row] resultsBlock:blk3];
    } else if (tableView == valuesTableView) {
        valueIdx = indexPath.row;
        if (indexPath.row == [valueList count]) {
            keysTableView.hidden = NO;
        } else {
            keysTableView.hidden = NO;
            [delegate keyValuePairSelected:[keyList objectAtIndex:keyIdx] value:[valueList objectAtIndex:indexPath.row]];
        }
    }
}

-(void)tableView:(UITableView *)tableView accessoryButtonTappedForRowWithIndexPath:(NSIndexPath *)indexPath {
	
}
@end
