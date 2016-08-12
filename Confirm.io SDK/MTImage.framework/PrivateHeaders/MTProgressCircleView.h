//
//  MTProgressCircleView.h
//  CommonUtilities
//
//  Created by Steve Hernandez on 9/23/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <UIKit/UIKit.h>

IB_DESIGNABLE
@interface MTProgressCircleView : UIView

@property (nonatomic, strong) IBInspectable UIColor *trackColor;
@property (nonatomic, strong) IBInspectable UIColor *borderColor;
@property (nonatomic, strong) IBInspectable UIColor *tintColor;             // background of progress circle
@property (nonatomic) IBInspectable CGFloat borderSize;                     // draw width of outer circle
@property (nonatomic) IBInspectable CGFloat borderOffsetMargin;             // distance between outercircle and inner circle
@property (nonatomic) IBInspectable CGFloat interierOffsetMargin;           // distance between center and inner circle
@property (nonatomic) IBInspectable CGFloat centerSize;						// draw radius of center circle.
@property (nonatomic) IBInspectable Boolean hideWhenAnimationStops;

@property (nonatomic) IBInspectable CGFloat maximumValue;       // largest possible value default 100
@property (nonatomic) IBInspectable CGFloat value;          // 0 to maximumValue


//ContiniousAnimationSupport
//Caution. Use of this method will prevent client from setting property 'value' and MaxValue.
-(void)startAnimating;
-(void)stopAnimating;

- (void)setValue:(CGFloat)value animated:(BOOL)animated;

@end
