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

@interface ViewController () <ConfirmCaptureDelegate>

@property (weak, nonatomic) IBOutlet UIButton *workflowButton;
@property (weak, nonatomic) IBOutlet UIButton *workflowFacialButton;

@property (weak, nonatomic) IBOutlet UILabel *statusLabel;
@property (weak, nonatomic) IBOutlet UILabel *progressLabel;

@property (strong, nonatomic)	ConfirmPayload*	payload;

@end

@implementation ViewController
@synthesize statusLabel, progressLabel;
@synthesize workflowButton, workflowFacialButton;

+ (ViewController*)controller
{
	ViewController* vc = [[ViewController alloc] initWithNibName:@"ViewController" bundle:nil];
	vc.edgesForExtendedLayout = UIRectEdgeLeft | UIRectEdgeRight | UIRectEdgeBottom;

	return vc;
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	self.title = @"Confirm.io Sample App";
	
	[self makeButtonNice:workflowButton];
	[self makeButtonNice:workflowFacialButton];
	
}

- (void)makeButtonNice:(UIButton*)button
{
	CALayer* layer = button.layer;
	
	layer.cornerRadius = 12;
	layer.borderColor = UIColor.darkGrayColor.CGColor;
	layer.borderWidth = 2;
	
	button.titleLabel.numberOfLines	= 0;
	button.titleLabel.textAlignment = NSTextAlignmentCenter;
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

- (IBAction)tappedWorkflow:(UIButton*)sender
{
	UINavigationController* nav = ConfirmCapture.singleton.confirmController;
	
	ConfirmCapture.singleton.delegate = self;
	ConfirmCapture.singleton.enableFacialMatch = NO;
	
	[self presentViewController:nav
					   animated:YES
					 completion:nil];
}

- (IBAction)tappedWorkflowFacial:(UIButton*)sender
{
	UINavigationController* nav = ConfirmCapture.singleton.confirmController;
	
	ConfirmCapture.singleton.delegate = self;
	ConfirmCapture.singleton.enableFacialMatch = YES;

	[self presentViewController:nav
					   animated:YES
					 completion:nil];
}

- (void)showResults:(IDModel*)validatedID facial:(FacialMatchResponse*)facialResponse
{
	ResultsController* 				rvc = ResultsController.controller;
	rvc.result = validatedID;
	rvc.facial = facialResponse;
	[self.navigationController pushViewController:rvc animated:YES];
}

#pragma mark - ConfirmCameraDelegate

// called when picture has been taken, image is valid object
- (void)ConfirmCaptureDidComplete:(ConfirmPayload*)payload
{
	[ConfirmSubmit.singleton submitIDCapturePayload:payload
										   onStatus:^(NSDictionary* _Nonnull info, ConfirmSubmitState state) {
											   NSString* title = info[kStatusInfoTitleKey];
											   NSString* message = info[kStatusInfoMessageKey];
											   
											   [self setStatus:title message:message];
										   }
										 onProgress:^(NSProgress* _Nonnull progress, ConfirmSubmitProgressType progressType) {
											 static NSTimeInterval 		lastProgress = 0;
											 NSTimeInterval 			rightNow = NSDate.timeIntervalSinceReferenceDate;
											 
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
										  onSuccess:^(IDModel * _Nullable validatedID, FacialMatchResponse * _Nullable facialResponse) {
											  [self showResults:validatedID facial:facialResponse];
											  [ConfirmCapture.singleton cleanup];
										  }
											onError:^(NSError * _Nonnull error, NSString * _Nullable guid) {
												
												NSLog(@"submission error %@", error.localizedDescription);
												[ConfirmCapture.singleton cleanup];
											}
	 ];
	[self dismissViewControllerAnimated:YES completion:NULL];
}

// called when user cancels VC via button
- (void)ConfirmCaptureDidCancel
{
	[self dismissViewControllerAnimated:YES completion:NULL];
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

