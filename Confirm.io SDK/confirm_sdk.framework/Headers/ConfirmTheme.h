//
//  ConfirmTheme.h
//  confirm-sdk
//
//  Created by Greg Peet on 5/8/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//


#ifndef kConfirmTheme
#define kConfirmTheme

#import <Foundation/Foundation.h>

/** The theme class for the SDK. The dedicated instance is @b sharedInstance. */
@interface ConfirmTheme : NSObject

/** @detailed The UIFont for the SDK's text appearance. 
 	The font should ideally be plain and devoid of stylistic traits.
 	@attention Set before presenting ConfirmCamera. */
@property (nonatomic, copy) UIFont 	*themeFont;

/** @detailed The UIColor responsible for SDK's text color.
 	Be mindful of contrast: keep the color light enough to appear against the background.
	@attention Set before presenting ConfirmCamera. */
@property (nonatomic, copy) UIColor *themeTextColor;

/** @detailed The UIColor responsible for SDK's outline color.
 	Be mindful of contrast: keep the color light enough to appear against the background.
	@attention Set before presenting ConfirmCamera. */
@property (nonatomic, copy) UIColor *themeOutlineColor;

/** @detailed The UIColor responsible for SDK's accent color.
 	Be mindful of contrast: keep the color light enough to appear against the background.
	@attention Set before presenting ConfirmCamera. */
@property (nonatomic, copy) UIColor *themeAccentColor;

/** The dedicated theme object for the SDK. Any other ConfirmTheme objects will be ignored. */
+ (ConfirmTheme*)sharedInstance;

/** The designated configuratator for setting a theme.
 	@param font The desired base font for the theme. Can be nil for default font.
 	@param textColor The desired text color for the theme. Can be nil for default color.
 	@param outlineColor The desired color for SDK outline elements. Can be nil for default color.
 	@param accentColor The desired color for SDK accents. Can be nil for default color.
*/
- (void)setFont:(UIFont*)font
	  textColor:(UIColor*)textColor
   outlineColor:(UIColor*)outlineColor
	accentColor:(UIColor*)accentColor;
@end


/** Use the following categories to configure non-SDK UI elements */  
@interface UIColor(confirmTheme)

+ (UIColor*)confirmTextColor;
+ (UIColor*)confirmOutlineColor;
+ (UIColor*)confirmAccentColor;

@end

@interface UIButton(confirmTheme)

- (void)adoptTheme:(NSString*)buttonTitle fontSize:(CGFloat)fontSize;
- (void)adoptTheme:(NSString*)buttonTitle fontSize:(CGFloat)fontSize resize:(BOOL)resize;
- (void)setColorize:(UIColor*)color;
@end

#endif