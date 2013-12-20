//
//  PDFViewController.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class PDFView;
@class Asset;

@interface PDFViewController : UIViewController <UIScrollViewDelegate>{
	PDFView *pdfView;
	Asset *asset;
    UIWebView *webView;
}
@property (nonatomic, retain) PDFView *pdfView;
@property (nonatomic, retain) IBOutlet UIWebView *webView;
@property (nonatomic, retain) Asset *asset;

-(IBAction)done:(id)sender;
@end
