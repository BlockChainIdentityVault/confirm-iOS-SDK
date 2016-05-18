//
//  ConfirmCameraVC.h
//  confirm-sdk
//
//  Created by roy on 1/7/16.
//  Copyright © 2016 confirm.io. All rights reserved.
//

#import <UIKit/UIKit.h>


typedef enum {
	ConfirmCaptureFront,
	ConfirmCaptureBack,
	ConfirmCaptureSelfie
} ConfirmCaptureSide;

@class ConfirmCameraVC;
@class ConfirmPayload;

@protocol ConfirmCameraDelegate <NSObject>

// called when picture has been taken, image is valid object
- (void)confirmCamera:(ConfirmCameraVC*)vc didComplete:(UIImage*)image;

// called when user cancels VC via button
- (void)confirmCameraDidDismiss:(ConfirmCameraVC*)vc;

// called when VC is dismissed (UINavigationController pop, button, etc)
- (void)confirmCameraWillBeDismissed:(ConfirmCameraVC*)vc;

@end


@interface ConfirmCameraVC : UIViewController

@property (nonatomic, assign)	id<ConfirmCameraDelegate> 	delegate;
@property (nonatomic, assign)	BOOL						backButtonHidden;		// default NO
@property (nonatomic, assign)	ConfirmCaptureSide			captureSide;
@property (nonatomic, retain)	ConfirmPayload*				payload;				// must be an instance of ConfirmPayload::payload 

// optional overrides
@property (nonatomic, retain)	NSString*					backButtonTitle;		// default <
@property (nonatomic, assign)	NSTimeInterval				firstTransitionTime;	// default 1.5s
@property (nonatomic, assign)	NSTimeInterval				autocaptureFadeTransitionTime;	// default 1.0s
@property (nonatomic, retain)	NSString*					initialCaption;			// default depends on captureSide
@property (nonatomic, retain)	NSString*					successString;			// default depends on captureSide

@property (nonatomic, retain)	NSDictionary*				configurations;

+ (ConfirmCameraVC*)controller;


@end
