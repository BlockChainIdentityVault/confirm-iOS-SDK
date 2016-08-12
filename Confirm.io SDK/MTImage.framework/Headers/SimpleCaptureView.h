//
//  SimpleCaptureView.h
//  MTImage
//
//  Created by clayton on 7/8/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SimpleCaptureView : UIView

/*!
 * @discussion The block that will be executed after an image is attempted to be captured by calling the captureImage function.
   @param image If an image is successfully captured, the captured image will be set to this parameter.
   @param error If an error occurs during block execution, the error will be set to this parameter.
 */
typedef void (^imageCaptureCompletionBlock)(UIImage *image, NSError *error);

/*!
 * @brief This property indicates whether the user’s phone’s back camera is active or not.
 */
@property (nonatomic, readonly) BOOL backCameraActive;

/*!
 * @discussion This function starts the video camera on the user’s phone.
 */
-(void)startVideo;

/*!
 * @discussion This function stops the video camera on the user’s phone.
 */
-(void)stopVideo;

/*!
 * @discussion This function switches between the front and back cameras on the user’s phone.
   @param animate Dictates whether a flipping animation should be used.
 */
-(void)toggleCameraWithAnimation:(BOOL)animate;

/*!
 * @discussion This function captures an image and when finished will execute the completionBlock parameter.
   @param completionBlock A block that contains two objects- a UIImage named image and an NSError named error. If an image is successfully captured, the captured image will be the image object. Likewise, if an image could not be captured, the error will be the error object.
 */
-(void)captureImage:(imageCaptureCompletionBlock)completionBlock;



@end
