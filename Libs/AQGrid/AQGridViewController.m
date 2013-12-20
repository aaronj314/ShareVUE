/*
 * AQGridViewController.m
 * AQGridView
*/
//  Created by Aaron Jones on 1/4/11.

#import "AQGridViewController.h"

@interface AQGridView (AQGridViewPrivate)
- (void) viewWillRotateToInterfaceOrientation: (UIInterfaceOrientation) orientation;
- (void) viewDidRotate;
@end

@implementation AQGridViewController

@synthesize clearsSelectionOnViewWillAppear=_clearsSelectionOnViewWillAppear;

- (void) _sharedGridViewDefaultSetup
{
	self.gridView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	self.gridView.autoresizesSubviews = YES;
	self.gridView.delegate = self;
	self.gridView.dataSource = self;
}

- (void) loadView
{
	AQGridView * aView = [[AQGridView alloc] initWithFrame: CGRectZero];
	self.gridView = aView;
	[aView release];
    
    [self _sharedGridViewDefaultSetup];
}

- (void) awakeFromNib
{
    [self _sharedGridViewDefaultSetup];
}

- (void) viewDidLoad
{
	[super viewDidLoad];
	[self.gridView reloadData];
	
	_popoverShowing = NO;
}

- (AQGridView *) gridView
{
	return ( (AQGridView *) self.view );
}

- (void) setGridView: (AQGridView *) value
{
	if ( [value isKindOfClass: [AQGridView class]] == NO )
	{
		[NSException raise: NSInvalidArgumentException format: @"-setGridView: called with non-AQGridView argument '%@'", NSStringFromClass([value class])];
	}
	
	self.view = value;
}

/*
 // The designated initializer.  Override if you create the controller programmatically and want to perform customization that is not appropriate for viewDidLoad.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    if ((self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil])) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/

/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/

- (void) viewWillAppear: (BOOL) animated
{
	if ( (_clearsSelectionOnViewWillAppear) && ([self.gridView indexOfSelectedItem] != NSNotFound) )
	{
		[self.gridView deselectItemAtIndex: [self.gridView indexOfSelectedItem] animated: NO];
	}
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Overriden to allow any orientation.
    return YES;
}

- (void) willRotateToInterfaceOrientation: (UIInterfaceOrientation) toInterfaceOrientation
								 duration: (NSTimeInterval) duration
{
	[self.gridView viewWillRotateToInterfaceOrientation: toInterfaceOrientation];
} 

- (void) didRotateFromInterfaceOrientation: (UIInterfaceOrientation) fromInterfaceOrientation
{
	[self.gridView viewDidRotate];
}

- (void)didReceiveMemoryWarning {
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


- (void)dealloc {
    [super dealloc];
}

#pragma mark -
#pragma mark Grid View Data Source

- (NSUInteger) numberOfItemsInGridView: (AQGridView *) gridView
{
	return ( 0 );
}


- (AQGridViewCell *) gridView: (AQGridView *) gridView cellForItemAtIndex: (NSUInteger) index
{
	return ( nil );
}

#pragma mark -
#pragma mark UIPopoverControllerDelegate methods

- (void)popoverControllerDidDismissPopover:(UIPopoverController *)popoverController
{
	_popoverShowing = NO;
}

@end
