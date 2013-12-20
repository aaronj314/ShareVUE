

//  Created by Aaron Jones on 1/4/11.

#import "AQGridViewCell.h"

enum
{
	AQGridViewCellSeparatorEdgeBottom	= (1 << 0),
	AQGridViewCellSeparatorEdgeRight	= (1 << 1)
};
typedef NSUInteger AQGridViewCellSeparatorEdge;

@interface AQGridViewCell (AQGridViewCellPrivate)

@property (nonatomic, retain) UIColor * separatorColor;
@property (nonatomic, assign) AQGridViewCellSeparatorStyle separatorStyle;
@property (nonatomic, assign) AQGridViewCellSeparatorEdge separatorEdge;

@property (nonatomic, assign) NSUInteger displayIndex;

@property (nonatomic, assign) BOOL hiddenForAnimation;

@end
