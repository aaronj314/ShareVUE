//
//  ProjectMaterialsGridView.h
//  ShareVUE
//
//  Created by Aaron Jones on 3/6/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "AQGridView.h"

@class PDFView;
@class DocumentGridViewCell;

@interface ProjectMaterialsGridView : NSObject <AQGridViewDataSource, AQGridViewDelegate, UIGestureRecognizerDelegate> {
    AQGridView *gridView;
	NSMutableArray *materials;
    
    NSUInteger emptyCellIndex;
    PDFView *pdfView;
}
@property (nonatomic, retain) IBOutlet AQGridView *gridView;
@property (nonatomic, retain) NSMutableArray *materials;

-(void)loadProjectMaterials:(Project *)project;
@end
