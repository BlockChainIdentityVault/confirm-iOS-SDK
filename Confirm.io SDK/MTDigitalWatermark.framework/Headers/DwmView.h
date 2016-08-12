//
//  DwmView.h
//  MTDigitalWatermark
//
//  Created by clayton on 6/9/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DwmAuthentication.h"
#import "DwmPayload.h"

#ifndef DwmViewTypes
#define DwmViewTypes
/*!
 @typedef DwmViewStyle
 
 @brief  Available styles for DwmView.
 
 @discussion Available styles for DwmView
 
 @field DVS_None    None.
 @field DVS_Guide   Show user instructions & card placement template.
 @field DVS_Guide_Fade  Show user instructions & card placement template. Fading animation.
 @field DVS_Guide_Only  Show the card placement template.
 
 */
typedef enum DwmViewStyle: NSInteger {
    /*! @brief None. */
    DVS_None,
    
    /*! @brief Show user instructions & card placement template. */
    DVS_Guide,
    
    /*! @brief Show user instructions & card placement template. Fading animation. */
    DVS_Guide_Fade,
    
    /*! @brief Show the card placement template. */
    DVS_Guide_Only
} DwmViewStyle;


/*!
 @typedef ESFProgressStyle
 
 @brief  Available styles for ESFProgress.
 
 @discussion Available styles for ESFProgress.
 
 @constant ESFProgressStyleNone    ESFProgressStyleNone.
 @constant ESFProgressStyleIndicators   ESFProgressStyleIndicators.
 @constant ESFProgressStyleCircle  ESFProgressStyleCircle.
 */
typedef NS_ENUM(NSUInteger, ESFProgressStyle) {
    ESFProgressStyleNone,
    ESFProgressStyleIndicators,
    ESFProgressStyleCircle
};

/*!
 @typedef ESFScanCompleteImageStyle
 
 @brief  Available styles for ESFScanCompleteImage.
 
 @discussion Available styles for ESFScanCompleteImage.
 
 @constant ESFScanCompleteImageStyleNone    ESFScanCompleteImageStyleNone.
 @constant ESFScanCompleteImageStyleDefault   ESFScanCompleteImageStyleDefault.
 @constant ESFScanCompleteImageStyleCustom  ESFScanCompleteImageStyleCustom.
 */
typedef NS_ENUM(NSUInteger, ESFScanCompleteImageStyle) {
    ESFScanCompleteImageStyleNone,
    ESFScanCompleteImageStyleDefault,
    ESFScanCompleteImageStyleCustom
};

/*!
 @typedef ESFScanArtifactOption
 
 @brief  Available options for ESFScanArtifact.
 
 @discussion Available options for ESFScanArtifact.
 
 @constant ESFScanArtifactOptionCardAndESFOnly    ESFScanArtifactOptionCardAndESFOnly.
 @constant ESFScanArtifactOptionCardPortrait   ESFScanArtifactOptionCardPortrait.
 */
typedef NS_OPTIONS(NSUInteger, ESFScanArtifactOption) {
    ESFScanArtifactOptionCardAndESFOnly		= 0,
    ESFScanArtifactOptionCardPortrait   = 1 << 0
};
#endif // DwmViewTypes

/*!
 ##DWM Delegate functions
 
 */

/*!
 @protocol dwmViewDelegate
 
 @brief The dwmViewDelegate protocol
 
 */
@protocol dwmViewDelegate <NSObject>

@required
/*!
 @brief Implement this delegate method to get the result of the DWM detection process.
 
 @param success Specified <b>YES</b> if successful, <b>NO</b> if failed.
 
 @param payLoad Payload to be passed to delegate as <b>DwmPayload</b>.
 
 @param dlImage Drivers license image to be passed to delegate as UIImage. This is cropped as best as possible to show only the card and no background information, as well as oriented right-side up.
 
 @param portrait License portrait to be passed to delegate as UIImage.
 
 */
- (void)detectCompleted:(BOOL)success payloadData:(DwmPayload *)payLoad dlImage:(UIImage *)dlImage portrait:(UIImage *)portrait;

@optional
/*!
 @brief Implement this delegate method to get SDK errors.
 
 @param message Message to be passed to delegate as NSString.
 
 */
- (void)detectError:(NSString *)message;

@end

@interface DwmView : UIView

@property (nonatomic, weak) id<dwmViewDelegate> delegate;

/*! @brief Determines if the video is shut off when detection is stopped. */
@property (nonatomic) BOOL saveEnergy;

/*! @brief Enable/Disable Card Detection. */
@property (nonatomic) BOOL cardDetectEnabled;

/*! @brief Default is true. Disable for when camera is stationary. Best left enabled when using Card Detect. */
@property (nonatomic) BOOL autoFocusContinuousEnabled;

/*! @brief Shows checkmark showing scan completed, even if no watermark detected. */
@property (nonatomic) BOOL alwaysShowCheckmarkOnCompletion;
@property (nonatomic) DwmViewStyle style;
@property (nonatomic) BOOL flipCardTextEnabled;
@property (nonatomic) ESFProgressStyle progressStyle;
@property (nonatomic, strong) UIColor *progressOnColor;
@property (nonatomic, strong) UIColor *progressOffColor;
@property (nonatomic) ESFScanCompleteImageStyle scanCompleteImageStyle;
@property (nonatomic, strong) UIImage *scanCompleteImage;
@property (nonatomic) ESFScanArtifactOption scanArtifactOptions;

/*!
 @brief Start detection process.
 
 @discussion Use this method to start the process of detecting a watermark. The parameter <b>maxDurationInSeconds</b> specifies in integers the amount of time in seconds you will scan for a watermark before timing out. Upon successful completion of scan, the <b>detectCompleted:payloadData:dlImage:portrait:</b> delegate method will be called. On failure, the <b>detectError:</b> delegate method will be called.
 
 @param maxDurationInSeconds Specify in integers the amount of time in seconds you will scan for a watermark before timing out.
 
 */
-(void)startDetect:(int)maxDurationInSeconds;

/*!
 @brief Forcibly stops the detection process.
 
 @discussion Use this method to stop the process of detecing a watermark, generally added to a UIViewController's <b>viewDidDisappear:</b> method.
 
 */
-(void)stopDetect;

@end
