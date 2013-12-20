//
//  ProjectMaterialsGridView.m
//  ShareVUE
//
//  Created by Aaron Jones on 3/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "ProjectMaterialsGridView.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "DocumentGridViewCell.h"
#import "CookieNavView.h"
#import "RootViewController.h"
#import "MGSplitViewController.h"
#import "PDFViewController.h"
#import "PDFView.h"

@implementation ProjectMaterialsGridView
@synthesize materials;
@synthesize gridView;

-(void)dealloc {
    [pdfView release];
	[materials release];
    [gridView release];
    [super dealloc];
}

- (id)initWithFrame:(CGRect)frame {
    self = [super init];
    if (self) {
        gridView = [[AQGridView alloc] initWithFrame:frame];
        gridView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
        gridView.delegate = self;
        gridView.dataSource = self;
        gridView.scrollEnabled = YES;
        emptyCellIndex = NSNotFound;
    }
    return self;
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
            hiddenCell = [[[AQGridViewCell alloc] initWithFrame: CGRectMake(0.0, 0.0, 133.0, 85.0) reuseIdentifier: EmptyIdentifier] autorelease];
        }
        
        hiddenCell.hidden = YES;
        return ( hiddenCell );
    }
    
    DocumentGridViewCell * cell = (DocumentGridViewCell *)[gridView dequeueReusableCellWithIdentifier: CellIdentifier];
    if ( cell == nil )
    {
        cell = [[[DocumentGridViewCell alloc] initWithFrame:CGRectMake(0.0, 0.0, 133.0, 85.0) reuseIdentifier:CellIdentifier] autorelease];
    }
    
    cell.project = [materials objectAtIndex: index];
    
    return cell;
}

-(CGSize)portraitGridCellSizeForGridView:(AQGridView *)gridView {
    return ( CGSizeMake(133.0, 85.0) );
}

- (void) gridView: (AQGridView *) gridView didSelectItemAtIndex: (NSUInteger) index {
	NSLog(@"Selection");
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
	
	/*NSString *myLabelText = @"<  Back To Project Details"; 
    CookieNav *cookie = [[CookieNav alloc] init];
	cookie.master = appDelegate.splitViewController.masterViewController;
    // ContentDetailViewController *cdetail = (ContentDetailViewController *)appDelegate.splitViewController.detailViewController;
	cookie.detail = self;
	cookie.masterBeforeDetail = NO;
    [appDelegate.rootViewController.cookieNavView pushWithTitle:myLabelText cookie:cookie];
	*/
	[gridView deselectItemAtIndex:index animated:NO];
    
    PDFViewController *controller = [[PDFViewController alloc] initWithNibName:@"PDFViewController" bundle:nil];
	controller.pdfView = pdfView;
	controller.asset = [materials objectAtIndex:index];
	[appDelegate.rootViewController presentModalViewController:controller animated:YES];
	[controller release];
}

-(void)loadProjectMaterials:(Project *)project {
    ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    AssetsResultsBlock blk2 = ^(NSMutableArray *list, NSError *error) {
        self.materials = list;
        [gridView reloadData];
    };
    [appDelegate.account assetsForProject:project resultsBlock:blk2];
}
@end
