//
//  MTImagingHelper-Private.h
//  MTImage
//
//  Created by Michael Callaghan on 1/25/16.
//  Copyright © 2016 MorphoTrust. All rights reserved.
//

#import <MTImage/MTImagingHelper.h>

@interface MTImagingHelper()

+ (UIImage *)makeUIImageFromCMSampleBuffer:(CMSampleBufferRef)sampleBuffer withPosition:(AVCaptureDevicePosition)position rawImage:(UIImage * __autoreleasing *)rawImage;

@end

