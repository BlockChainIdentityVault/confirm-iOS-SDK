//
//  ConfirmTheme.h
//  confirm-sdk
//
//  Created by roy on 1/20/16.
//  Copyright © 2016 confirm.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface UIFont(confirmTheme)

+ (UIFont*)confirmFont:(CGFloat)fontSize;
+ (UIFont*)confirmBoldFont:(CGFloat)fontSize;
+ (UIFont*)confirmLightFont:(CGFloat)fontSize;
+ (UIFont*)confirmMediumFont:(CGFloat)fontSize;
+ (UIFont*)confirmSemiBoldFont:(CGFloat)fontSize;

@end

@interface UIColor(confirmTheme)

+ (UIColor*)confirmHUDColor;
+ (UIColor*)confirmBlue;

@end
