//
//  VideoLoadingStatusView.h
//  TechnicolorDailies
//
//  Created by Aaron Jones on 1/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface VideoLoadingStatusView : UIView {
    UIActivityIndicatorView *spinner;
	
}
@property (nonatomic, retain) IBOutlet UIActivityIndicatorView *spinner;
@end
