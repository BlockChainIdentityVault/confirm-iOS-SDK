//
//  ConfirmCameraDemo.m
//  Sample
//
//  Created by roy on 5/11/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import "ConfirmCameraDemo.h"
#import "InterstitialVC.h"

#import <confirm_sdk/confirm_sdk.h>

@interface ConfirmCameraDemo() <ConfirmCameraDelegate>

@property (strong, nonatomic)	ConfirmPayload* 			payload;
@property (strong, nonatomic)	UINavigationController*		navigationController;
@property (weak, nonatomic)		UIViewController*			topVC;
@property (weak, nonatomic)		UIViewController*			parent;

@property (copy, nonatomic)		void						(^completion)(ConfirmPayload* payload);
@end

@implementation ConfirmCameraDemo

+ (ConfirmCameraDemo*)singleton
{
	static dispatch_once_t token = 0;
	static ConfirmCameraDemo* singleton = nil;
	
	dispatch_once(&token, ^{
		singleton = [[ConfirmCameraDemo alloc] init];
	});
	return singleton;
}

- (void)runDemo:(UIViewController*)parent completion:(void(^)(ConfirmPayload* payload))completion
{
	self.parent = parent;
	self.completion = completion;
	
	// create payload to be added to by ConfirmCameraVC
	self.payload = ConfirmPayload.payload;
	
	self.navigationController = parent.navigationController;
	self.navigationController.navigationBarHidden = YES;
	self.topVC = self.navigationController.topViewController;
	
	[self pushFrontSideInstructions];
}

- (void)pushFrontSideInstructions
{
	UIViewController* interstitial = [InterstitialVC controller:@"Instructions for capturing front of ID" 
													 completion:^(BOOL next) {
														 if (next)
															 [self pushFrontSide];
														 else
															 [self cancel];
													 }];
	[self.navigationController pushViewController:interstitial animated:YES];
}

- (void)pushFrontSide
{
	ConfirmCameraVC* camVC = ConfirmCameraVC.controller;
	
	camVC.delegate = self;
	camVC.captureSide = ConfirmCaptureFront;
	camVC.payload = self.payload;	// the view controller needs to know where to put the data
	
	[self.navigationController pushViewController:camVC animated:YES];
}

- (void)pushBackSideInstructions
{
	UIViewController* interstitial = [InterstitialVC controller:@"Instructions for capturing back of ID" 
													 completion:^(BOOL next) {
														 if (next)
															 [self pushBackSide];
														 else
															 [self.navigationController popViewControllerAnimated:YES];
													 }];

	[self.navigationController pushViewController:interstitial animated:YES];
}

- (void)pushBackSide
{
	ConfirmCameraVC* camVC = ConfirmCameraVC.controller;
	
	camVC.delegate = self;
	camVC.captureSide = ConfirmCaptureBack;
	camVC.payload = self.payload;	// the view controller needs to know where to put the data
	
	[self.navigationController pushViewController:camVC animated:YES];
}

- (void)pushSelfieInstructions
{
	UIViewController* interstitial = [InterstitialVC controller:@"Instructions for capturing selfie" 
													 completion:^(BOOL next) {
														 if (next)
															 [self pushSelfie];
														 else
															 [self.navigationController popViewControllerAnimated:YES];
													 }];
	
	[self.navigationController pushViewController:interstitial animated:YES];
}

- (void)pushSelfie
{
	ConfirmCameraVC* camVC = ConfirmCameraVC.controller;
	
	camVC.delegate = self;
	camVC.captureSide = ConfirmCaptureSelfie;
	camVC.payload = self.payload;	// the view controller needs to know where to put the data
	
	[self.navigationController pushViewController: camVC animated:YES];
}

#pragma mark - ConfirmCameraDelegate

// called when picture has been taken, image is valid object
- (void)confirmCamera:(ConfirmCameraVC*)vc didComplete:(UIImage*)image
{
	switch (vc.captureSide) {
		case ConfirmCaptureFront:
			[self pushBackSideInstructions];
			break;
		case ConfirmCaptureBack:
			[self pushSelfieInstructions];
			break;
		case ConfirmCaptureSelfie:
			[self allDone];
			break;
	}
}

// called when user cancels VC via button
- (void)confirmCameraDidDismiss:(ConfirmCameraVC*)vc
{
	switch (vc.captureSide) {
		case ConfirmCaptureFront:
			[self cancel];
			break;
		case ConfirmCaptureBack:
			[self.navigationController popViewControllerAnimated:YES];
			break;
		case ConfirmCaptureSelfie:
			[self.navigationController popViewControllerAnimated:YES];
			break;
	}
}

// called when VC is dismissed (UINavigationController pop, button, etc)
- (void)confirmCameraWillBeDismissed:(ConfirmCameraVC*)vc
{
}

#pragma mark -

- (void)allDone
{
	[self cleanup:YES];
}

- (void)cleanup:(BOOL)success
{
	if (self.completion)
		self.completion(success ? self.payload : nil);
	
	self.payload = nil;	// release payload
	
	[self.navigationController popToViewController:self.topVC animated:YES];
	self.navigationController = nil;
}

- (void)cancel
{
	[self cleanup:NO];
}

@end
