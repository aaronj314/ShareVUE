//
//  SignInViewController_iPad.m
//  ShareVUE
//
//  Created by Aaron Jones on 2/22/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import "SignInViewController_iPad.h"
#import "ShareVUEAppDelegate_iPad.h"
#import "ProjectsGridViewController.h"
#import "RootViewController.h"
#import "ProjectsGridViewController.h"
#import "MGSplitViewController.h"
#import "CookieNavView.h"

@implementation SignInViewController_iPad

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)dealloc
{
    [super dealloc];
}

- (void)didReceiveMemoryWarning
{
    // Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
    
    // Release any cached data, images, etc that aren't in use.
}

#pragma mark - View lifecycle

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view from its nib.
	[[NSNotificationCenter defaultCenter] removeObserver:self];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardDidShow:) name:UIKeyboardDidShowNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardWillHide:) name:UIKeyboardWillHideNotification object:nil];
}

CGRect oldframe;
-(void)keyboardDidShow:(NSNotification *)aNotification {
    
    UIInterfaceOrientation orient = [UIApplication sharedApplication].statusBarOrientation;
    
    if (orient == UIInterfaceOrientationLandscapeLeft || orient == UIInterfaceOrientationLandscapeRight) {
        NSDictionary* info = [aNotification userInfo];
        NSValue *aValue = [info objectForKey:UIKeyboardFrameEndUserInfoKey];
        CGRect keyboardFrame = [aValue CGRectValue];
        //NSLog(@"SHOW Keyboard Rect=%@", NSStringFromCGRect(keyboardFrame));
        
        oldframe = loginBox.frame;
		[UIView animateWithDuration:0.2f animations:^{
			loginBox.frame = CGRectMake(oldframe.origin.x, oldframe.origin.y -100, oldframe.size.width, oldframe.size.height);
		}];
		
    }
	
}

-(void)keyboardWillHide:(NSNotification *)aNotification {
	UIInterfaceOrientation orient = [UIApplication sharedApplication].statusBarOrientation;
    if (orient == UIInterfaceOrientationLandscapeLeft || orient == UIInterfaceOrientationLandscapeRight) {
        [UIView animateWithDuration:0.2f animations:^{
			loginBox.frame = oldframe;
		}];
    }
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    // Return YES for supported orientations
	//return YES;
    return ((interfaceOrientation == UIInterfaceOrientationLandscapeLeft) || (interfaceOrientation == UIInterfaceOrientationLandscapeRight));
}

-(void)signOut:(id)sender {
    [[NSNotificationCenter defaultCenter] postNotificationName:@"SignOutNotification" object:nil];
	ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
    userName.text = nil;
    password.text = nil;
	appDelegate.account = nil;
	//appDelegate.splitViewController.detailViewController = [NSNull null];
	//appDelegate.splitViewController.masterViewController = [NSNull null];
   
	appDelegate.projectsGridViewController.projects = nil;
	[appDelegate.projectsGridViewController.gridView reloadData];
	[appDelegate.rootViewController.cookieNavView flushView];
	appDelegate.rootViewController.mainViewController = appDelegate.projectsGridViewController;
	[appDelegate.rootViewController presentModalViewController:appDelegate.signInViewController animated:YES];
}

-(void)signIn:(id)sender {
	//hide old errors 
    [errorBanner setHidden:YES];
	errorlbl.text=@"";//clear text
    
#ifndef DEBUG
	if ([userName.text length] == 0 || [password.text length] == 0) {
		//UIAlertView *alertView = [[[UIAlertView alloc] initWithTitle:@"Sign In Error" message:@"Must enter user name or password" delegate:self cancelButtonTitle:@"Try Again" otherButtonTitles:nil] autorelease];
		//[alertView show];
		errorlbl.text = @"Must enter user name or password.";
		[errorBanner setHidden:NO];
		 [super earthquake: loginBox ];
		
		return;
	}
#endif
 
	
#ifdef DEBUG
    userName.text = TEST_USER_NAME;
    password.text = TEST_PASSWD;
#endif
	
	SignInResultsBlock blk = ^(Account *account, NSError *error){
		if (error) {
			/*UIAlertView *alertView = [[[UIAlertView alloc] initWithTitle:@"Sign In Error" message:@"Authentication error" delegate:self cancelButtonTitle:@"Try Again" otherButtonTitles:nil] autorelease];
			[alertView show];*/
            NSLog(@"ERROR-SIGNIN::%@",error);
            errorlbl.text = @"You have an authentication error!";
            [errorBanner setHidden:NO];			
            [super earthquake:loginBox];
            return;
		} else {
			ShareVUEAppDelegate_iPad *appDelegate = APP_IPAD_DELEGATE();
			
			if (appDelegate->locked) {
				/*UIAlertView *alertView = [[[UIAlertView alloc] initWithTitle:@"Sign In Error" message:@"Location service for the device must be enabled" delegate:self cancelButtonTitle:@"Try Again" otherButtonTitles:nil] autorelease];
				[alertView show];
                 */
                errorlbl.text = @"Location service for this device must be enabled.";
                [errorBanner setHidden:NO];			
                [super earthquake:loginBox];
				return;
			}
			
			appDelegate.account = account;
			appDelegate.rootViewController.statusView.hidden = NO;
            [appDelegate.projectsGridViewController loadProjectsFromService];
            
		
			appDelegate.rootViewController.currentLoggedIn.text = appDelegate.account.user.userName;
			
            // hide signin view
            [appDelegate.rootViewController dismissModalViewControllerAnimated:YES];
			
			
			
            //[appDelegate.rootViewController.view addSubview:appDelegate.projectsGridViewController.view];

		} 
		
	} ;
	
	[Account signInWithUsername:userName.text password:password.text resultsBlock:blk];

     
}
@end
