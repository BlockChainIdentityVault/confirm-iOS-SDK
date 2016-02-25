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
} ConfirmCaptureSide;

@protocol ConfirmCameraDelegate <NSObject>

// called when picture has been taken, image is valid object
- (void)confirmCameraDidComplete:(UIImage*)image;

// called when user cancels VC via button
- (void)confirmCameraDidDismiss;

// called when VC is dismissed (UINavigationController pop, button, etc)
- (void)confirmCameraWillBeDismissed;

@end

@interface ConfirmCameraVC : UIViewController

@property (nonatomic, assign)	id<ConfirmCameraDelegate> 	delegate;
@property (nonatomic, assign)	BOOL						backButtonHidden;		// default NO

@property (nonatomic, assign)	ConfirmCaptureSide			captureSide;
// optional overrides
@property (nonatomic, assign)	NSTimeInterval				firstTransitionTime;	// default 1.5s
@property (nonatomic, assign)	NSTimeInterval				autocaptureFadeTransitionTime;	// default 1.0s
@property (nonatomic, retain)	NSString*					initialCaption;			// default depends on captureSide
@property (nonatomic, retain)	NSString*					successString;			// default depends on captureSide

+ (ConfirmCameraVC*)controller;


@end
