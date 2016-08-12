//
//  DwmAuthentication.h
//  MTDigitalWatermark
//
//  Created by clayton on 6/9/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "DwmPayload.h"
#import "DwmStatesEnum.h"

/*!
 @class DwmAuthentication
 
 @brief The DwmAuthentication class
 
 @discussion    The DwmAuthentication class
 
 @superclass SuperClass: NSObject 
 
 */
@interface DwmAuthentication : NSObject

/*!
 @brief Block for use with <b>decodeImage</b> methods.
 
 @param payload Payload returned upon completion of image decoding.
 
 @param error Error returned (nil if successful).
 */
typedef void (^decodeCompletionBlock)(DwmPayload *payload, NSError *error);

/*!
 @brief Perform image decoding.
 
 @discussion Use this method to perform image decoding by inputting a single image; returns a Payload if found. The parameter <b>image</b> should be cropped as best as possible and oriented right-side up. If no <b>primaryRect</b> is available, use the <b>decodeImage:completed:</b> class method.
 
 @param image Single image to be decoded.
 
 @param primaryRect Rect in which image can be found, if available.
 
 @param completionBlock See <b>decodeCompletionBlock</b>.
 
 */
-(void)decodeImage:(UIImage *)image withPrimary:(CGRect)primaryRect completed:(decodeCompletionBlock)completionBlock;

/*!
 @brief Perform image decoding.
 
 @discussion Use this method to perform image decoding by inputting a single image; returns a Payload if found. The parameter <b>image</b> should be cropped as best as possible and oriented right-side up. If a discrete <b>primaryRect</b> is available, use the <b>decodeImage:withPrimary:completed:</b> instance method.
 
 @param image Single image to be decoded.
 
 @param completionBlock See <b>decodeCompletionBlock</b>.
 
 */
+(void)decodeImage:(UIImage *)image completed:(decodeCompletionBlock)completionBlock;

/*!
 @brief Check for DWM.
 
 @discussion Takes in a <b>state</b> and <b>issue date</b> and returns <b>YES</b> if the document should contain a DWM, <b>NO</b> if not.
 
 @param state State of document
 
 @param date Issue date of document
 
 @param error Error to be passed by reference (nil if successful).
 
 */
-(BOOL)documentContainsDWM:(DwmStates)state issueDate:(NSDate *)date errorInfo:(NSError **)error;

/*!
 @brief Check for DWM.
 
 @discussion Takes in a <b>state</b> and <b>issue date</b> and returns <b>YES</b> if the document should contain a DWM, <b>NO</b> if not.
 
 @param state State of document
 
 @param date Issue date of document
 
 @param error Error to be passed by reference (nil if successful).
 
 */
+(BOOL)documentContainsDWM:(DwmStates)state issueDate:(NSDate *)date errorInfo:(NSError **)error;

/*!
 @brief Check for DWM.
 
 @discussion Takes in a <b>state</b> and <b>date components</b> and returns <b>YES</b> if the document should contain a DWM, <b>NO</b> if not.
 
 @param state State of document
 
 @param day Issue day of document
 
 @param month Issue month of document
 
 @param year Issue year of document
 
 @param error Error to be passed by reference (nil if successful).
 
 */
-(BOOL)documentContainsDWM:(DwmStates)state issueDay:(int)day issueMonth:(int)month issueYear:(int)year errorInfo:(NSError **)error;

/*!
 @brief Check for DWM.
 
 @discussion Takes in a <b>state</b> and <b>date components</b> and returns <b>YES</b> if the document should contain a DWM, <b>NO</b> if not.
 
 @param state State of document
 
 @param day Issue day of document
 
 @param month Issue month of document
 
 @param year Issue year of document
 
 @param error Error to be passed by reference (nil if successful).
 
 */
+(BOOL)documentContainsDWM:(DwmStates)state issueDay:(int)day issueMonth:(int)month issueYear:(int)year errorInfo:(NSError **)error;

@end
