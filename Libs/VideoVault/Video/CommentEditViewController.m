//
//  CommentEditViewController.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "CommentEditViewController.h"
#import "Comment.h"

@implementation CommentEditViewController
@synthesize modalController, timecode, comment;

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
 

// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}



// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations.
    return YES;
}

-(IBAction)done:(id)sender {
	Comment *c = [Comment commentWithName:@"" value:comment.text timecode:0.0];
	[modalController addComment:c];
	[modalController dismissModalViewControllerAnimated:YES];
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


- (void)dealloc {
	[timecode release];
	[comment release];
	[modalController release];
    [super dealloc];
}


@end
