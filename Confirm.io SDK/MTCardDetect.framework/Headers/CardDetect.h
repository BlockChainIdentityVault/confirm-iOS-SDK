//
//  CardDetect.h
//  CardDetect
//
//  Created by Wu, Ted on 7/8/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreImage/CoreImage.h>
#import <ImageIO/ImageIO.h>

#define _MIN_FOCUS      50
#define _MIN_EXPOSURE   30
#define _MAX_GLARE      2000

struct Quality
{
    bool  poorQuality;
    float focus;
    float exposure;
    float color;
    
#ifdef _USE_MTVHCARDMETRICS
    float glare;
    float dwm;
    float fakeid;
    
    //JRM 2016-05-03 : was testing G2 metrics
    //float g2focus;
    //float g2exposure;
    //float g2color;
#endif  //_USE_MTVHCARDMETRICS
};

@interface CardDetect : NSObject

typedef void (^detectCardCompletionBlock)(UIImage *cardImage, CGPoint * corners, float *score);

+ (float)calcFocus:(UIImage *)image;
+ (struct Quality)calcQuality:(UIImage *)image;
+ (struct Quality)calcQualityGradient:(UIImage *)image;
+ (void)detectCard:(UIImage *)image completed:(detectCardCompletionBlock)completionBlock;
+ (BOOL) checkCorners:(CGPoint *)corners withImage:(UIImage *)currentFrame;

/*!
 * @discussion This function applies bilateral filtering to the input image. The filtering reduces unwanted noise while keeping sharp edges to improve the selfie to DL matching quality. It is normally slower than other image smoothing filters, such as the Gaussian filter.
   @param image Color or grayscale image declared as a UIImage type.
   @param size The size of the filter. A larger size will result in stronger smoothing and take longer time to process. The size value must be a positive integer. It is recommended not to exceed a size greater than 15.
   @param sigmaColor Filter sigma in the color space. A larger value means that farther colors within the pixel neighborhood will be mixed together, resulting in larger areas of semi-equal color. This value must be a positive integer. There is no provided value range because the value is very specific to the image size and application type.
   @param sigmaSpace Filter sigma in the coordinate space. A larger value means that farther pixels will influence each other as long as their colors are close enough. This value must be a positive integer. There is no provided value range because the value is very specific to the image size and application type.
   @return The filtered image.
 */
+ (UIImage *)bilateralFilter:(UIImage *)image filterSize:(int)size sigmaColor:(float)sigmaColor sigmaSpace:(float)sigmaSpace;



#ifdef _USE_MTVHCARDMETRICS
+ (void) calcDWMMetrics:(UIImage*)image withFaceRect:(CGRect*)face returnDWM:(float*) pDWM returnFakeID:(float*) pFakeID;
+ (void) calcDWMMetricsOnFullImage:(UIImage*)image returnDWM:(float*) pDWM returnFakeID:(float*)pFakeID withDPI:(int*)pKnownDPI;
#endif  //_USE_MTVHCARDMETRICS


@end

