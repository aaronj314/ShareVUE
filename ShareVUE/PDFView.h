//
//  PDFView.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@class TiledPDFView;

@interface PDFView : UIScrollView <UIScrollViewDelegate> {
	CGPDFDocumentRef document;
	
	// The TiledPDFView that is currently front most
	TiledPDFView *pdfView;
	// The old TiledPDFView that we draw on top of when the zooming stops
	TiledPDFView *oldPDFView;
	
	// A low res image of the PDF page that is displayed until the TiledPDFView
	// renders its content.
	UIImageView *backgroundImageView;
	
	
	// current pdf zoom scale
	CGFloat pdfScale;
	
	CGPDFPageRef page;
}
@property (nonatomic, assign) CGPDFDocumentRef document;
@end

