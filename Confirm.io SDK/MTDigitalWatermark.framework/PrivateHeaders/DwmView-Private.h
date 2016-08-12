//
//  DwmView-Private.h
//  MTDigitalWatermark
//
//  Created by Michael Callaghan on 1/25/16.
//  Copyright © 2016 MorphoTrust. All rights reserved.
//

#import <MTDigitalWatermark/DwmView.h>

@protocol dwmQAViewDelegate <NSObject>

@optional
- (void)saveRawImage:(UIImage *)rawImage;
- (void)saveBeforeCardDetectImage:(UIImage *)beforeCardDetectImage;

@end

@interface DwmView()

@property (nonatomic) BOOL recordCameraData; //save the camera data to the camera roll.
@property (nonatomic, weak) id<dwmQAViewDelegate> qaDelegate;
@property (nonatomic, strong) UIImage *rawImage;
@property (nonatomic, strong) UIImage *beforeCardDetectImage;
//TODO: If we decide to keep this, think about moving it to scanArtifactOptions
@property (nonatomic) BOOL disableESFDetection;

@end
