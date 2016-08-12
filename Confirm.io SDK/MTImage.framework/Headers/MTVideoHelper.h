//
//  MTVideoHelper.h
//  MTImage
//
//  Created by clayton on 6/22/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AVFoundation/AVFoundation.h>

//callback delegate setup for captureoutput
@protocol libVideoDelegate <NSObject>

@optional
//implement this delegate to get the buffer frames after you startVideoCapture
-(void)getLastSampleBuffer:(CMSampleBufferRef)lastCMSampleBufferRef faceRect:(CGRect)face faceYawAngle:(CGFloat)yawAngle faceRollAngle:(CGFloat)rollAngle barcodeData:(NSString *)data;
//implement this delegate to get the results of takeSillImage
-(void)getNewStillImage:(UIImage *)stillImage;

@end

//interface for Video Imaging Utility class
@interface MTVideoHelper : NSObject

//used to set the video resolution
typedef enum AVCaptureSessionPreset: NSInteger
{
    High,
    Low,
    Medium,
    Photo,
    _640x480,
    _1280x720,
    _1920x1080 //only available if using Back camera
} AVCaptureSessionPreset;

@property (nonatomic, weak) id<libVideoDelegate> delegate;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer *previewLayer;
@property (nonatomic, strong) AVCaptureSession *session;
@property (nonatomic, strong) AVCaptureDevice *device;

@property (nonatomic) BOOL showCenterBox; //turns on/off the box around the face showing face is in center
@property (nonatomic) BOOL showFaceBoundingBox; //turns on/off the box around the face in the previewlayer
@property (nonatomic) BOOL showBarcodeBoundingBox; //turns on/off the box around a barcode (PDF 417, QR code, etc) in the previewlayer
@property (nonatomic) CGFloat minHeadSize; //used for centering the head and reduction of image distortion on selfies
@property (nonatomic) CGFloat maxHeadSize; //used for centering the head and reduction of image distortion on selfies
@property (nonatomic) AVCaptureFlashMode flashMode; //used to set flash mode (Automatic, On, Off)
@property (nonatomic) AVCaptureAutoFocusRangeRestriction autoFocusRange; //calls the AVCaptureFocusModeAutoFocus

//AVMetaObjectType Support --- Default: Face and PDF417 are enabled
@property (nonatomic) BOOL faceFindSupport; //enable/disable face finding support in video
@property (nonatomic) BOOL pdf417Support; //enable/disable PDF417 barcode reading support in vidoe
@property (nonatomic) BOOL qrCodeSupport; //enable/disable QR Code barcode reading support in video

//init function to setup the Video session
//avLayerVideoGravity can either be: AVLayerVideoGravityResizeAspectFill or AVLayerVideoGravityResizeAspect
//DWM must use AVLayerVideoGravityResizeAspect
//typical pixelformats
// kCVPixelFormatType_420YpCbCr8BiPlanarFullRange - HC DWM
// kCVPixelFormatType_32BGRA - Image processing
- (id)initWithAVCaptureSessionPreset:(AVCaptureSessionPreset)avPreset devicePosition:(AVCaptureDevicePosition) position previewVideoGravity:(NSString *) avLayerVideoGravity pixelFormat:(int)pixelFormat;

//Instance Methods
//start the video camera, output is sent to the getLastSampleBuffer delegate
-(void)startVideoCapture;
//stop the video camera
-(void)stopVideoCapture;
//toggle the camera device in use (Front/Back)
-(void)toggleCameraWithAnimation:(BOOL)animate;
//takes a still image, output is sent to the getNewStilLImage delegate (startVideoCapture must be called first)
-(void)takeStillPicture;
//calls the AVCaptureFocusModeAutoFocus
-(void)autoFocusCamera;
//calls the AVCaptureFocusMode and set it to continuous
-(void)autoFocusContinuousCamera;
//returns a UIView that shows the live video preview, set size equal to how big on the screen you want the video
-(UIView *)getPreviewView:(CGRect)viewSize withCenterBox:(BOOL)showBox;
//call this method to reset the barcode detector, needed for iOS8
-(void)clearBarcodeData;
//call this method to reset the face detection data, needed for iOS8
-(void)clearFaceData;

//(Property Setter Overload) used for centering the head and reduction of image distortion on selfies
-(void)setMinHeadSize:(CGFloat)minHeadSize maxHeadSize:(CGFloat)maxHeadSize;
//turn on LED as a torch with brightness level 0.1 - 1.0
-(void)enableTorchWithLevel:(float)brightness;
//turn off the LED torch
-(void)disableTorch;

@end
