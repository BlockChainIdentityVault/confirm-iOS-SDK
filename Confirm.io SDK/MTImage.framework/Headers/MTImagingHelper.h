//
//  MTImagingHelper.h
//  
//  Created by Daniel Poder on 9/17/13.
//  Copyright (c) 2013 MorphoTrust. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVFoundation.h>
#import "FaceFeatures.h"

//interface for Video Imaging Utility class
@interface MTImagingHelper : NSObject

//convert a color into an image of that color
+(UIImage *)imageFromColor:(UIColor *)color;

//used to convert a CMSampleBuffer to UIImage.  The device orientation is accounted for in correctly orienting the CGImageRef behind the UIImage output.
+(UIImage *)makeUIImageFromCMSampleBuffer:(CMSampleBufferRef)sampleBuffer withPosition:(AVCaptureDevicePosition)position;

//returns a UIImage from a known data format Grayscale
//[MTImagingHelper makeUIImageFromGrayScaleData:data withWidth:imageWidth height:imageheight bytesPerRow:imageWidth];
+(UIImage *) makeUIImageFromGrayScaleData:(unsigned char *)data withWidth:(int)width height:(int)height bytesPerRow:(int)bytesPerRow;

//returns a UIImage from a known data format RGB
//[MTImagingHelper makeUIImageFromRGBData:data withWidth:imageWidth height:imageheight bytesPerRow:imageWidth];
+(UIImage *) makeUIImageFromRGBData:(unsigned char *)data withWidth:(int)width height:(int)height bytesPerRow:(int)bytesPerRow;

//returns a UIImage from a known data format BGRA
//[MTImagingHelper makeUImageFromData:data withWidth:imageWidth height:imageheight bytesPerRow:imageWidth];
+(UIImage *) makeUIImageFromBGRAData:(unsigned char *)data withWidth:(int)width height:(int)height bytesPerRow:(int)bytesPerRow;

//returns a UIImage from a known data format RGBA
//[MTImagingHelper makeUImageFromData:data withWidth:imageWidth height:imageheight bytesPerRow:imageWidth];
+(UIImage *) makeUIImageFromRGBAData:(unsigned char *)data withWidth:(int)width height:(int)height bytesPerRow:(int)bytesPerRow;

//returns a UIImage from a known data format BGRA, caller must free the returned unsigned char*
//[MTImagingHelper makeUImageFromData:data withWidth:imageWidth height:imageheight bytesPerRow:imageWidth];
+(unsigned char *) convertBGRAtoRGB:(unsigned char *)data withWidth:(int)width height:(int)height bytesPerRow:(int)bytesPerRow;





@end
