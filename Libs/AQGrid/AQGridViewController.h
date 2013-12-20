

//  Created by Aaron Jones on 1/4/11.

#import <UIKit/UIKit.h>
#import "AQGridView.h"

#define POPOVER_SIZE CGSizeMake( 345, 525 )

@interface AQGridViewController : UIViewController <AQGridViewDelegate, AQGridViewDataSource, UIPopoverControllerDelegate>
{
	@private
	BOOL _clearsSelectionOnViewWillAppear;
	@protected
	BOOL _popoverShowing;
}

@property (nonatomic, retain) AQGridView * gridView;
@property (nonatomic) BOOL clearsSelectionOnViewWillAppear;

@end
