//
//  UIImage+ImagingHelper.h
//  MTImage
//
//  Created by clayton on 6/22/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "FaceFeatures.h"

@interface UIImage (ImagingHelper)

//Returns 0-100 scale of focus for the given image.
-(int)calculateFocus;
-(int)calculateFocusScore: (int)step
                     skip: (int)skip
              edgePercent: (int)edgePercent; // new image gradient based method

//returns a brightness  Range 0-255 (0 black, 255 white)
-(int)calculateBrightness;
-(int)calculateBrightness:(CGRect)rect;
-(int)calculateBrightness:(int)clrs edgePercentSkip:(int)percent;


//returns an unsigned char *, caller must free the returned unsigned char*
-(unsigned char *)makeDataArray;

//detect if UIImage is grayScale
-(BOOL)isGrayScale;

//converts UIImage to grayScale using CoreImage
-(UIImage *)makeGrayScale;

//converts a UIIMage to grayscale with a scale factor
-(UIImage *)makeGrayScaleAndScale:(int)scalar;

/*!
 * @discussion This function takes as input a UIImage that has the face oriented in portrait format.
   @param accuracy The accuracy at which the client would like to detect a face inside of an image. There are only two available options- HighAccuracy and LowAccuracy.
   @return A FaceFeatures object containing the detected facial features.
 */
-(FaceFeatures)getFaceFeaturesWithAccuracy:(FaceDetectionAccuracy)accuracy; //default - logging disabled to avoid spam.
-(FaceFeatures)getFaceFeaturesWithAccuracy:(FaceDetectionAccuracy)accuracy withLogging:(BOOL)verbose;

//takes as input a UIImage and uses Sonic for face and eye detection
//-(FaceFeatures)getSonicFaceFeatures;

//draws indicators on the face for eyes, and mouth
-(UIImage *)drawFacialLocationsLeftEye:(CGPoint)leftEye rightEye:(CGPoint)rightEye mouth:(CGPoint)mouth faceBox:(CGRect)faceRect;

// draw text into a UIImage at specified location, font size, and color
-(UIImage *)drawText:(NSString*) text  atPoint:(CGPoint) point atColor:(UIColor *) color fontSize:(int)size;

//returns a resized Image
-(UIImage *)resizeToSize:(CGSize)newSize;

//returns a cropped Image (Scaled based on IMAGE coordinates of the actual image size)
//CGRect is assumed to be Image coordinates
//use 0 for PaddingPercent if you do not want to pad the crop box.  Use 75 if you are passing in a FaceRect bounds (from the iOS face finder) as this will properly crop the entire head
-(UIImage *)cropImageAtCoordinates:(CGRect)rectOrig withPaddingPercent:(float)percent ;

//returns a cropped CGImage (Scaled based on screen coordinates to the actual image size)
//CGRect is assumed to be Screen coordinates
//use 0 for PaddingPercent if you do not want to pad the crop box.  Use 75 if you are passing in a FaceRect bounds (from the iOS face finder) as this will properly crop the entire head
-(UIImage *)cropImageAtCoordinates:(CGRect)rectOrig withPaddingPercent:(float)percent viewSize:(CGSize)viewSize;

//returns a rotated image based on the angle parameter (45,90, etc...),
-(UIImage *)rotatedByAngle:(CGFloat)angle;

- (UIImage *)imageAtRect:(CGRect)rect;
- (UIImage *)imageByScalingProportionallyToMinimumSize:(CGSize)targetSize;
- (UIImage *)imageByScalingProportionallyToSize:(CGSize)targetSize;
- (UIImage *)imageByScalingToSize:(CGSize)targetSize;
- (UIImage *)imageRotatedByRadians:(CGFloat)radians;
- (UIImage *)imageRotatedByDegrees:(CGFloat)degrees;

@end
