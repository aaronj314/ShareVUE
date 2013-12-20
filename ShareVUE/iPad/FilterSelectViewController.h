//
//  FilterSelectViewController.h
//  ShareVUE
//
//  Created by Aaron Jones on 5/5/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

@class Project;

@interface FilterSelectViewController : UIViewController <UITableViewDelegate, UITableViewDataSource> {
    id delegate;
    NSArray *keyList;
    NSArray *valueList;
    UITableView *keysTableView;
    UITableView *valuesTableView;
    Project *project;
    
    UIImageView *background;
}
@property (nonatomic, retain) id delegate;
@property (nonatomic, retain) NSArray *keyList;
@property (nonatomic, retain) NSArray *valueList;
@property (nonatomic, retain) Project *project;
@property (nonatomic, retain) IBOutlet UITableView *keysTableView;
@property (nonatomic, retain) IBOutlet UITableView *valuesTableView;
@end
