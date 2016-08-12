//
//  EmbeddedVC.m
//  Sample
//
//  Created by roy on 5/17/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import "EmbeddedVC.h"
#import <confirm_sdk/confirm_sdk.h>

@interface EmbeddedVC () < ConfirmCameraDelegate >

@property (weak, nonatomic)		IBOutlet UIView *			container;
@property (strong, nonatomic)	ConfirmPayload* 			payload;
@property (strong, nonatomic)	ConfirmCameraVC* 			camVC;

@end

@implementation EmbeddedVC

+ (EmbeddedVC*)controller
{
	return [[EmbeddedVC alloc] initWithNibName:@"EmbeddedVC" bundle:nil];
}

- (void)viewDidLoad 
{
    [super viewDidLoad];
	self.payload = ConfirmPayload.payload;
	
	self.camVC = ConfirmCameraVC.controller;
	
	self.camVC.delegate = self;
	self.camVC.captureSide = ConfirmCaptureSelfie;
	self.camVC.payload = self.payload;	// the view controller needs to know where to put the data

	[self.camVC embedControllerIn:self inView:self.container];
}

- (void)confirmCamera:(ConfirmCameraVC*)vc didComplete:(UIImage*)image
{
	// do something with the payload / image in usual circumstances
	[self.delegate embededFinished];
}

- (void)confirmCameraDidDismiss:(ConfirmCameraVC*)vc
{
	[self.delegate embededFinished];
}

- (void)confirmCameraWillBeDismissed:(ConfirmCameraVC*)vc
{
	self.camVC = nil;
}

- (void)dealloc
{
	self.payload = nil;	
	self.camVC = nil;
}

@end
