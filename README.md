#![Confirm logo](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-logo_43x34.png) Confirm.io (BETA)

[Confirm.io](http://www.confirm.io/) provides simple, safe, and secure mobile ID authentication solutions. Our cloud API and paired image capture SDK empower applications to more seamlessly collect customer information and authenticate the identity of their users. 

This SDK requires an API key issued by Confirm.io in order to submit documents to our cloud. If you wish to test out the SDK, [please contact Confirm](http://www.confirm.io/#!contact/i66dd) to receive your demo API key.

## Requirements

• Xcode 7.0 or later
• Supports target deployment of iOS Version 8.1 and architectures arm7, arm7s, arm64

## Sample app

Seeing how someone else is using the SDK is the easiest way to learn. To see the SDK in action, feel free to check out the bundled [Sample](https://github.com/confirm-io/confirm-iOS-SDK/tree/master/Sample) app by opening `Sample/Sample.xcodeproj` in Xcode.

## Setup

To include the SDK framework in your own project...

1. Download latest version of the SDK
2. Add the confirm_sdk.framework to your Xcode project ![Framework location](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-iOS-SDK_framework-location.jpeg)
3. In the `General` tab of the project's `TARGETS` section - drag `confirm_sdk.framework` to "Embedded Binaries" ![Framework embedding](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-iOS-SDK_framework-embedding.jpeg)
4. Include `#import <confirm_sdk/confirm_sdk.h>` in the source files that will use the SDK.
5. In `Build Settings` turn `Enable Bitcode` to NO
6. Depending on where you added the confirm_sdk.framework to your source tree, you may have to add a "Framework Search Path" to your `Build Settings`. Something like `$(PROJECT_DIR)/Frameworks` may be required (if you put the framework in a folder called "Frameworks")

## Sample Code

There are two parts to the SDK - intelligent ID image capture, and submission to Confirm.io's secure cloud for authentication.

### Integrate as a ViewController

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

Bring up the view controller to capture the front of the ID:

```obj-c
- (IBAction)takeFrontPicture:(UIButton*)sender
{
	self.cameraVC = ConfirmCameraVC.controller;
	self.cameraVC.delegate = self;
	self.cameraVC.captureSide = ConfirmCaptureFront;

	[self presentViewController:self.cameraVC animated:YES completion:nil];
}
```

Bring up the view controller to capture the back of the ID:

```obj-c
- (IBAction)takeBackPicture:(UIButton*)sender
{
	self.cameraVC = ConfirmCameraVC.controller;
	self.cameraVC.delegate = self;
	self.cameraVC.captureSide = ConfirmCaptureBack;

	[self presentViewController:self.cameraVC animated:YES completion:nil];
}
```

Write delegate methods to receive the captured images or view controller dismissal

```obj-c
- (void)confirmCameraDidComplete:(UIImage*)image
{
	self.frontImage = image;
	// ...
}

- (void)confirmCameraWillBeDismissed
{
	self.cameraVC = nil;
	// ...
}

- (void)confirmCameraDidDismiss
{
	// ...
}
```

#### Delegate methods

There are three delegate calls that the client can receive while using the Confirm Camera ViewController:

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

### Submit to Confirm.io's API

After both the front and back of the ID have been captured, the images can then be sent to Confirm.io's cloud API for data extraction and authentication. 

Before submission to the Confirm API, developers must obtain an API key from Confirm's team directly. It is highly recommended that mobile developers leverage Confirm's consumer key authentication protocals when submitting images directly to Confirm's API. To learn more, [please visit our documentation](https://confirm.readme.io/docs/authentication).

The code containing verification API is located in the object `ConfirmSubmit`.

To set the API key, make the call

```obj-c
ConfirmSubmit.singleton.apiKey = @"{YOUR_API_KEY_HERE}";
```

_A good place for this initialization is in the UIApplication delegate method `application:didFinishLaunchingWithOptions:`,  but it can be made anywhere prior to the actual ConfirmSubmit API call._

Once you have the front and back images captured via `ConfirmCameraVC` object, the developer now needs to submit those images to the Confirm.io API for authentication:

```obj-c
•••
@property (nonatomic, strong) ConfirmSession* session;  // property of calling object
•••
- (void)submit
{
	if (self.frontImage == nil || self.backImage) return;
	
	self.session = [ConfirmSubmit.singleton submitIDWithFrontImage: self.frontImage
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
											  self.session = nil;
										  } 
										    onError:^(NSError *error, NSString* guid) {
											  [self showError:error.localizedDescription];
											  self.session = nil;
										  }
	 ];
}
```

###### return value
The `ConfirmSession` object returned can be used at any time prior to the `onSuccess` or `onError` blocks get called to cancel the transaction.

This can simply be done by a standard

```obj-c
- (IBAction)didTapCancelButton:(UIButton*)sender
{
	[self.session cancel];
	self.session = nil;
}
```

*NOTE*: Since network calls are taking place, the blocks will be called asynchronously at some later time, so the developer would most likely want to block user interface in some manner - most usually to not make successive calls to `submitIDWithFrontImage:andBackImage:onStatus:onProgress:onSuccess:onError` before the first call has a chance to complete. This can easily be done by setting the parent view's `userInteractionEnabled` to NO before the call, and to YES on either success or error.

###### onStatus:

This block will be called at various state transitions, and has an `NSDictionary` containing helpful, human readible strings to indicate the progress of the various states.

Once the ID's serve GUID is available, it will also become available in the `kStatusInfoGuidKey` key of the info parameter.

###### onProgress:

This block will be called during network upload and download progress. It will return an NSProgress object that can be inspected for data transmission `completedUnitCount` and `totalUnitCount`, and also an enumerated type indicating whether it is an upload or download progress event.

###### onSuccess:

This block will be called if all the network calls succeed and API returns with an authentication result. The ID information will be contained in the `IDModel` data structure called `validatedID`. No more block calls will be made after this block is received.

###### onError:

This block will be called if there was a network error, or if Confirm's API was unable to provide an authentication result. Confirm's API occasionally returns an `unknown` status for submissions that are damaged by shadow and glare, as well as for submissions that don't include a document in them. For more information on the statuses returned by our API, [please visit our API docs](https://confirm.readme.io/docs/idsguid).

The error as to what happened will be provided in the `NSError`, and no more block calls will be made after this block is received.


#### Hints & Tips

• Allowing the user to retake either the back or the front is a good thing
