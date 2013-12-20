/*
 * AQGridViewUpdateItem.m
 * AQGridView
 * 
*/
//  Created by Aaron Jones on 1/4/11.

#import "AQGridViewUpdateItem.h"

@implementation AQGridViewUpdateItem

@synthesize originalIndex=_index, newIndex=_newIndex, action=_action, animation=_animation, offset=_offset;

- (id) initWithIndex: (NSUInteger) index action: (AQGridViewUpdateAction) action animation: (AQGridViewItemAnimation) animation
{
	self = [super init];
	if ( self == nil )
		return ( nil );
	
	_index = index;
	_action = action;
	_animation = animation;
	
	return ( self );
}

- (void) setNewIndex: (NSUInteger) value
{
	NSAssert(self.action == AQGridViewUpdateActionMove, @"newIndex set on a non-move update item");
	_newIndex = value;
}

- (NSString *) description
{
	NSString * actionDesc = @"<Unknown>";
	switch ( _action )
	{
		case AQGridViewUpdateActionInsert:
			actionDesc = @"Insert";
			break;
		case AQGridViewUpdateActionDelete:
			actionDesc = @"Delete";
			break;
		case AQGridViewUpdateActionMove:
			actionDesc = @"Move";
			break;
		case AQGridViewUpdateActionReload:
			actionDesc = @"Reload";
			break;
		default:
			break;
	}
	
	NSString * animationDesc = @"<Unknown>";
	switch ( _animation )
	{
		case UITableViewRowAnimationFade:
			animationDesc = @"Fade";
			break;
		case UITableViewRowAnimationRight:
			animationDesc = @"Right";
			break;
		case UITableViewRowAnimationLeft:
			animationDesc = @"Left";
			break;
		case UITableViewRowAnimationTop:
			animationDesc = @"Top";
			break;
		case UITableViewRowAnimationBottom:
			animationDesc = @"Bottom";
			break;
		case UITableViewRowAnimationNone:
			animationDesc = @"None";
			break;
		case UITableViewRowAnimationMiddle:
			animationDesc = @"Middle";
			break;
		default:
			break;
	}
	
	return ( [NSString stringWithFormat: @"%@{index=%u, action=%@, animation=%@, offset=%.02f}", [super description], (unsigned)_index, actionDesc, animationDesc, _offset] );
}

- (NSComparisonResult) compare: (AQGridViewUpdateItem *) other
{
	if ( _index > other->_index )
		return ( NSOrderedDescending );
	else if ( _index < other->_index )
		return ( NSOrderedAscending );
	return ( NSOrderedSame );
}

- (NSComparisonResult) inverseCompare: (AQGridViewUpdateItem *) other
{
	return ( [other compare: self] );
}

- (NSUInteger) index
{
	// handle case where offset is negative and would cause index to wrap
	if ( (_offset < 0) && (abs(_offset) > _index) )
		return ( 0 );
	
	return ( _index + _offset );
}

@end
