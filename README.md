#![Confirm logo](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-logo_43x34.png) Confirm.io
# confirm-iOS-SDK



provides easy id verification, etc. etc.

## Sample app

Seeing how someone else is using the SDK is the easiest way to learn...

1. Download latest version of the SDK
2. Open the `SampleApp` folder and follow the instructions in the `README.md` file enclosed.

## Requirements

• Xcode 7.0 or later
• Supports target deployment of iOS Version 8.1 and architectures arm7, arm7s, arm64

## Setup

To include the SDK framework in your own project...

1. Download latest version of the SDK
2. Add the confirm_sdk.framework to your Xcode project
3. In the `General` tab of the project's `TARGETS` section - drag `confirm_sdk.framework` to "Embedded Binaries"
4. Include `#import <confirm_sdk/confirm_sdk.h>` in the source files that will use the SDK.
5. In `Build Settings` turn `Enable Bitcode` to NO
6. Depending on where you added the confirm_sdk.framework to your source tree, you may have to add a "Framework Search Path" to your `Build Settings`. Something like `$(PROJECT_DIR)/Frameworks` may be required (if you put the framework in a folder called "Frameworks")

## Integration

The Confirm.io SDK ships as an iOS Framework, which is to say it contains the executable code, the resources, and the Objective-C header files necessary to run the identification validation code. The framework needs to be added to your Xcode project in order to use it.

#### Xcode Project

1. Copy the Confirm.io framework `confirm_sdk.framework` to some place convenient in your project source tree.
2. Include `confirm_sdk.framework` in your Xcode project by dragging it into the project window: ![Confirm logo](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-iOS-SDK_framework-location.jpeg)
3. Link to `confirm_sdk.framework` in your Xcode project by dragging it from your project file list to the `Embedded Binaries` section of the `General` tab in your App's `TARGETS` settings.![Confirm logo](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-iOS-SDK_framework-embedding.jpeg)
4. At this point, your Xcode iOS App project should be configured to use the Confirm.io framework SDK.


#### Source Usage

There are two parts to the SDK - intelligent ID image capture, and server validation.

##### Camera / Image Capture View Controller

The Confirm.io framework provides a UIViewController subclass that provides assisted and intelligent ID image capture called `ConfirmCameraVC`. This UIViewController can be used as you would any other controller - either presenting it modally, or pushing it in a UINavigationController.

To use it in a parent view controller / object, add the `ConfirmCameraDelegate` protocol to the object.

```obj-c

#import <confirm_sdk/confirm_sdk.h>

@interface YourViewController () <ConfirmCameraDelegate>

// ...
@property (strong, nonatomic) ConfirmCameraVC* cameraVC;
// ...

@end

```

Then to bring up the view controller (for the front side of the ID, for example)

```obj-c

- (IBAction)takeFrontPictureWithCameraVC:(UIButton*)sender
{
	self.cameraVC = ConfirmCameraVC.controller;
	self.cameraVC.delegate = self;
	self.cameraVC.captureSide = ConfirmCaptureFront;

#if WITHIN_NAVIGATION
	[self.navigationController pushViewController:self.cameraVC animated:YES];
#else
	[self presentViewController:self.cameraVC animated:YES completion:nil];
#endif
}
```

There are three delegate calls that need to be implemented by the client.

###### - (void)confirmCameraDidComplete:(UIImage*)image

The first delegate call is the method call that occurs after a capture has been performed:  When your object gets this call, the `image` parameter will contain the UIImage captured. The developer should retain this object for later submission to the validation API.

This is the primary call that the developer should use to then perform a transition action, either dismissing the ConfirmCameraVC object, or popping it from the UINavigationController.

###### - (void)confirmCameraWillBeDismissed

This call is made back to the delegate to inform them that the UIViewController would really like to go away. In the case of the above example instantiation with `self.cameraVC`, the developer should implement:

```obj-c
- (void)confirmCameraWllBeDismissed
{
	self.cameraVC = nil;	// release ConfirmCameraVC memory
}
```

###### - (void)confirmCameraDidDismiss

This call is made back to the delegate after the back button is pressed. A back button is added by default, but can be overridden by setting `backButtonHidden` to `YES`; 

The goal with this delegate method is to trigger the transition that should occur for a 'cancel' operation. 

If the view controller was presented, it should be dimissed via `dismissViewControllerAnimated:completion:` selector. If it was pushed onto a UINavigationController, then call `popViewControllerAnimated:`. 

This method will not be called if the ConfirmCameraVC is pushed onto a UINavigationController, and the UINavigationItem's back button is pressed. In this case, view controller cleanup will be automatic, and the `confirmCameraWillBeDismissed` method will be called.

See the Sample app included in the SDK for reference.


##### ID Verification

In order to use the ID verification server APIs, the developer needs to obtain an API key from Confirm.io. 

**➡︎➡︎➡︎ information on how to do this goes here ⬅︎⬅︎⬅︎**

The code containing verification API is located in the object `ConfirmSubmit`.

To set the API key, make the call

```obj-c
	ConfirmSubmit.singleton.apiKey = @"{API key obtained from Confirm.io}";
```

Without the braces, of course.

A good place for this initialization is in the UIApplication delegate method `application:didFinishLaunchingWithOptions:`,  but it can be made anywhere prior to the actual ConfirmSubmit API call.

Once you have the front and back images captured via `ConfirmCameraVC` object, the developer now needs to submit those images to the Confirm.io API for validation.

The primary method is `submitIDWithFrontImage:andBackImage:onStatus:onProgress:onSuccess:onError`, and can be implemented as minimally as:

```obj-c
- (void)submit
{
	if (self.frontImage == nil)
		return;
	if (self.backImage == nil)
		return;
		
	[ConfirmSubmit.singleton submitIDWithFrontImage: self.frontImage
									   andBackImage:self.backImage
										   onStatus:^(NSDictionary* _Nonnull info, ConfirmSubmitState state) {
											   NSString* title = info[kStatusInfoTitleKey];
											   NSString* message = info[kStatusInfoMessageKey];
											   [self setStatus:title message:message state:state];
										   }
										 onProgress:^(NSProgress* progress, ConfirmSubmitProgressType progressType) {
											 [self displayProgressType:progressType percent:100 * progress.completedUnitCount / progress.totalUnitCount];
										 }
										  onSuccess:^(IDModel *validatedID) {
											  [self showResults:validatedID];
										  } 
										    onError:^(NSError *error, NSString* guid) {
											  [self showError:error.localizedDescription];
										  }
	 ];
}
```
Since network calls are taking place, the blocks will be called asynchronously at some later time, so the developer would most likely want to block user interface in some manner - most usually to not make successive calls to `submitIDWithFrontImage:andBackImage:onStatus:onProgress:onSuccess:onError` before the first call has a chance to complete. This can easily be done by setting the parent view's `userInteractionEnabled` to NO before the call, and to YES on either success or error.

###### status block

This block will be called at various state transitions, and has an `NSDictionary` containing helpful, human readible strings to indicate the progress of the various states.
Once the ID's serve GUID is available, it will also become available in the `kStatusInfoGuidKey` key of the info parameter.

###### progress block

This block will be called during network upload and download progress. It will return an NSProgress object that can be inspected for data transmission `completedUnitCount` and `totalUnitCount`, and also an enumerated type indicating whether it is an upload or download progress event.

###### success block

This block will be called if all the network calls succeed. The ID information will be contained in the `IDModel` data structure called `validatedID`. No more block calls will be made after this block is received.

###### error block

This block will be called if all the network calls succeed. The error as to what happened will be provided in the `NSError`. No more block calls will be made after this block is received.


#### Hints & Tips

• Allowing the user to retake either the back or the front is a good thing

