//
//  CookieNavView.h
//  ShareVUE
//
//  Created by Aaron Jones on 3/2/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "CookieNav.h"
#import "CookieNavStack.h"

@interface CookieNavView : UIView {
	CookieNavStack *navStack;
}
@property (nonatomic, retain) CookieNavStack *navStack;
-(void)flushView;
-(void)pushWithTitle:(NSString *)title cookie:(CookieNav *)cookie;
-(void)pop;
-(void)popToRoot;
@end
