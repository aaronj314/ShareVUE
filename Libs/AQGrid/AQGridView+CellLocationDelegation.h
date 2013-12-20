

 //  Created by Aaron Jones on 1/4/11.

#import <Foundation/Foundation.h>
#import "AQGridView.h"

@interface AQGridView (CellLocationDelegation)
- (void) delegateWillDisplayCell: (AQGridViewCell *) cell atIndex: (NSUInteger) index;
@end
