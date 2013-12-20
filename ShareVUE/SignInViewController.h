//
//  SignInViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//


#import <UIKit/UIKit.h>


@interface SignInViewController : UIViewController {
    UITextField *userName;
    UITextField *password;
    IBOutlet UIView *loginBox;
    IBOutlet UILabel *errorlbl;
    IBOutlet UIImageView *errorBanner;
}
@property (nonatomic, retain) IBOutlet UITextField *userName;
@property (nonatomic, retain) IBOutlet UITextField *password;
@property (nonatomic,retain)IBOutlet UIView *loginBox;
@property (nonatomic,retain)IBOutlet UILabel *errorlbl;
@property (nonatomic,retain)IBOutlet UIImageView *errorBanner;



- (void)earthquake:(UIView*)itemView;
- (void)earthquakeEnded:(NSString *)animationID finished:(NSNumber *)finished context:(void *)context;

-(IBAction)signIn:(id)sender;
-(IBAction)singOut:(id)sender;
@end
