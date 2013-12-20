//
//  BaseTableViewController.h
// 
//
//  Created by Aaron Jones on 1/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>


@interface BaseTableViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> {
	UITableView *tableView;
}
@property (nonatomic, retain) UITableView *tableView;

-(id)initWithStyle:(UITableViewStyle)style;
@end;
