//
//  ViewController.m
//  Sample
//
//  Created by roy on 2/1/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import "ViewController.h"
#import "ResultsController.h"

#import <confirm_sdk/confirm_sdk.h>

@interface NSString(Sample)
+ (NSString*)memoryString:(int64_t)value;
@end

@interface ViewController () <ConfirmCameraDelegate>

@property (weak, nonatomic) IBOutlet UIImageView *frontImageView;
@property (weak, nonatomic) IBOutlet UIImageView *backImageView;
@property (weak, nonatomic) IBOutlet UIButton *submitButton;
@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UILabel *progressLabel;

@property (strong, nonatomic)	UIImage* frontImage;
@property (strong, nonatomic)	UIImage* backImage;

@property (strong, nonatomic)	ConfirmCameraVC* confirmCameraVC;
@end

@implementation ViewController
@synthesize frontImageView, backImageView, submitButton;
@synthesize statusLabel, progressLabel;
@synthesize confirmCameraVC;

+ (ViewController*)controller
{
	ViewController* vc = [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
	vc.edgesForExtendedLayout = UIRectEdgeLeft | UIRectEdgeRight | UIRectEdgeBottom;

	return vc;
}

- (void)viewDidLoad
{
	self.title = @"Confirm.io Sample App";

	submitButton.enabled = NO;
	
	[super viewDidLoad];
}

- (void)setStatus:(NSString*)title message:(NSString*)message
{
	NSString* blurb = title;
	
	if (message)
		blurb = [blurb stringByAppendingFormat:@"\n%@", message];
	
	statusLabel.text = blurb;
}

- (void)didReceiveMemoryWarning
{
	[super didReceiveMemoryWarning];
	// Dispose of any resources that can be recreated.
}

#pragma mark - UX

- (IBAction)didTapFront:(UIButton *)sender
{
	self.confirmCameraVC = ConfirmCameraVC.controller;
	confirmCameraVC.delegate = self;
	confirmCameraVC.captureSide = ConfirmCaptureFront;
	
	[self presentViewController:confirmCameraVC
					   animated:YES
					 completion:nil];
}

- (IBAction)didTapBack:(UIButton *)sender
{
	self.confirmCameraVC = ConfirmCameraVC.controller;
	confirmCameraVC.delegate = self;
	confirmCameraVC.captureSide = ConfirmCaptureBack;
	
	[self presentViewController:confirmCameraVC
					   animated:YES
					 completion:nil];
}

- (IBAction)didTapSubmit:(UIButton *)sender
{
	submitButton.hidden = YES;
	
	self.view.userInteractionEnabled = NO;
	
	[ConfirmSubmit.singleton submitIDWithFrontImage:frontImageView.image
									   andBackImage:backImageView.image
										   onStatus:^(NSDictionary* _Nonnull info, ConfirmSubmitState state) {
											   NSString* title = info[kStatusInfoTitleKey];
											   NSString* message = info[kStatusInfoMessageKey];
											   
											   [self setStatus:title message:message];
										   }
										 onProgress:^(NSProgress* _Nonnull progress, ConfirmSubmitProgressType progressType) {
											 static NSTimeInterval 	lastProgress = 0;
											 NSTimeInterval 			rightNow = CACurrentMediaTime();
											 
											 if (progress.completedUnitCount == progress.totalUnitCount) {
												 progressLabel.text = @"";
											 } else if (rightNow-lastProgress > 1.0) {	// throttle progress to every second
												 NSString* 		blurb = [NSString stringWithFormat:@"%@ %@ out of %@",
																		 progressType == ConfirmSubmitUploadProgress ? @"Uploading" : @"Downloading",
																		 [NSString memoryString:progress.completedUnitCount],
																		 [NSString memoryString:progress.totalUnitCount]];
												 
												 progressLabel.text = blurb;
												 lastProgress = rightNow;
											 }
										 }
										  onSuccess:^(IDModel *validatedID) {
											  [self showResults:validatedID];
											  submitButton.hidden = NO;
											  self.view.userInteractionEnabled = YES;
										  } onError:^(NSError *error, NSString* guid) {
											  [self setStatus:@"submission error" message:error.localizedDescription];
											  submitButton.hidden = NO;
											  self.view.userInteractionEnabled = YES;
										  }
	 ];
}

- (void)showResults:(IDModel*)validatedID
{
	ResultsController* 				rvc = ResultsController.controller;
	rvc.result = validatedID;
	[self.navigationController pushViewController:rvc animated:YES];
}

#pragma mark - ConfirmCameraDelegate

// called when picture has been taken, image is valid object
- (void)confirmCameraDidComplete:(UIImage*)image
{
	switch (confirmCameraVC.captureSide) {
		case ConfirmCaptureFront:
			self.frontImage = image;
			frontImageView.image = image;
			frontImageView.backgroundColor = UIColor.clearColor;
			break;
		case ConfirmCaptureBack:
			self.backImage = image;
			backImageView.image = image;
			backImageView.backgroundColor = UIColor.clearColor;
			break;
	}
	[self confirmCameraDidDismiss];
	
	submitButton.enabled = self.frontImage != nil && self.backImage != nil;
}

// called when user cancels VC via button
- (void)confirmCameraDidDismiss
{
	[self dismissViewControllerAnimated:YES completion:NULL];
}

// called when VC is dismissed (UINavigationController pop, button, etc)
- (void)confirmCameraWillBeDismissed
{
	self.confirmCameraVC = nil;
}

- (void)dealloc
{
}

@end

@implementation NSString(Sample)

+ (NSString*)memoryString:(int64_t)value
{
	double dval = value;
	
	if (dval < 1024)
		return [NSString stringWithFormat:@"%d B", (int)dval];
	else {
		dval /= 1024.0;
		if (dval < 1024)
			return [NSString stringWithFormat:@"%0.1f KB", dval];
		else {
			dval /= 1024.0;
			if (dval < 1024)
				return [NSString stringWithFormat:@"%0.1f MB", dval];
			else {
				dval /= 1024.0;
				if (dval < 1024)
					return [NSString stringWithFormat:@"%0.1f GB", dval];
				else {
					dval /= 1024.0;
					if (dval < 1024)
						return [NSString stringWithFormat:@"%0.1f TB", dval];
					
				}
				
			}
		}
	}
	return nil;
}

@end

