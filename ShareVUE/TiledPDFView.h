//  TiledPDFView.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/9/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#import <UIKit/UIKit.h>


@interface TiledPDFView : UIView {
	CGPDFPageRef pdfPage;
	CGFloat myScale;
}

- (id)initWithFrame:(CGRect)frame andScale:(CGFloat)scale;
- (void)setPage:(CGPDFPageRef)newPage;

@end
