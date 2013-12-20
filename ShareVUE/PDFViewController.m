    //
//  PDFViewController.m
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "PDFViewController.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "RootViewController.h"
#import "PDFView.h"

@implementation PDFViewController
@synthesize pdfView;
@synthesize asset;
@synthesize webView;

- (void)dealloc {
    [asset release];
    [pdfView release];
    [webView release];
    [super dealloc];
}

-(CGPDFDocumentRef)openDocument:(CFURLRef)url {
	CGPDFDocumentRef myDocument = CGPDFDocumentCreateWithURL(url);
	if (myDocument == NULL) {
		return 0;
	}
	if (CGPDFDocumentIsEncrypted (myDocument)
		|| !CGPDFDocumentIsUnlocked (myDocument)
		|| CGPDFDocumentGetNumberOfPages(myDocument) == 0) {
		CGPDFDocumentRelease(myDocument);
		return 0;
	}
	return myDocument;
}

-(CGPDFDocumentRef)document {
	NSString *filePath = [[NSBundle mainBundle]
						  pathForResource:@"MobileWireframe" ofType:@"pdf"];
	NSURL *url = [[NSURL alloc] initFileURLWithPath:filePath];
	CGPDFDocumentRef document = [self openDocument:(CFURLRef)url];
	[url release];
	return document;
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
/*
- (void)loadView {
	//self.view = [[[UIView alloc] initWithFrame:CGRectZero] autorelease];
	//self.view.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	//self.view.autoresizesSubviews = YES;
	//pdfView = [[PDFView alloc] initWithFrame:CGRectMake(0, 0, 703, 748)];
	//pdfView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight | UIViewAutoresizingFlexibleRightMargin | UIViewAutoresizingFlexibleBottomMargin;
	//pdfView.autoresizesSubviews = YES;
	//pdfView.document = [self document];
	//[pdfView load];
	//[self.view addSubview:pdfView];
	//UIWebView *webView = [[UIWebView alloc] initWithFrame:CGRectZero];//CGRectMake(0, 0, 703, 748)];
	//webView.autoresizingMask =  UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
	//NSString *urlAddress = [[NSBundle mainBundle] pathForResource:@"MobileWireframe" ofType:@"pdf"];
	
	//NSURL *url = asset.url;//[NSURL fileURLWithPath:urlAddress];
	//NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
	//[webView loadRequest:requestObj];
	//webView.scalesPageToFit = YES;
	//[self.view addSubview:webView];
	//[webView release];
}
*/


// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
    NSURL *url = asset.url;//[NSURL fileURLWithPath:urlAddress];
	NSURLRequest *requestObj = [NSURLRequest requestWithURL:url];
	[webView loadRequest:requestObj];
	webView.scalesPageToFit = YES;
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

-(IBAction)done:(id)sender {
    ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    [appDelegate.rootViewController dismissModalViewControllerAnimated:YES];
}


- (void)viewDidUnload {
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}


@end
