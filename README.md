#![Confirm logo](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-logo_43x34.png) Confirm.io (BETA)

[Confirm.io](http://www.confirm.io/) provides simple, safe, and secure mobile ID authentication solutions. Our cloud API and paired image capture SDK empower applications to more seamlessly collect customer information and authenticate the identity of their users. 

This SDK requires an API key issued by Confirm.io in order to submit documents to our cloud. If you wish to test out the SDK, [please contact Confirm](http://www.confirm.io/#!contact/i66dd) to receive your demo API key.

## Requirements

• Xcode 7.0 or later
• Supports target deployment of iOS Version 8.1 and architectures arm7, arm7s, arm64

## Sample app

Seeing how someone else is using the SDK is the easiest way to learn. To see the SDK in action, feel free to check out the bundled [Sample](https://github.com/confirm-io/confirm-iOS-SDK/tree/master/Sample) app by opening `Sample/Sample.xcodeproj` in Xcode.

## Setup

### Via Pods

### Manual download

1. Download the latest version

To include the SDK framework in your own project...

1. [Download latest version of the SDK](https://github.com/confirm-io/confirm-iOS-SDK/archive/master.zip)
2. Add the confirm_sdk.framework to your Xcode project 
![Framework location](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-iOS-SDK_framework-location.jpeg)
3. In the `General` tab of the project's `TARGETS` section, drag `confirm_sdk.framework` to `Embedded Binaries`
![Framework embedding](https://s3-us-west-2.amazonaws.com/confirm.public/web-images/confirm-iOS-SDK_framework-embedding.jpeg)
4. Include `#import <confirm_sdk/confirm_sdk.h>` in the source files that will use the SDK.
5. In `Build Settings` turn `Enable Bitcode` to NO
6. Depending on where you added the confirm_sdk.framework to your source tree, you may have to add a "Framework Search Path" to your `Build Settings`. Something like `$(PROJECT_DIR)/Frameworks` may be required (if you put the framework in a folder called "Frameworks")

## Integration

The SDK is split into two core components:

1. `ConfirmCapture` - Intelligent document image capture of both the front and back of the user's ID.
2. `ConfirmSubmit` - Submission of captured imagery and data to api.confirm.io (requires API key)

### Introduction

The first step toward integration is to include and leverage confirm's UINavigationController subclass, `ConfirmCapture` controller, to expose the intelligent capture views to grab images of the end user's ID:

```obj-c
#import <confirm_sdk/confirm_sdk.h>

@interface SampleViewController () <ConfirmCaptureDelegate>

// ...
- (IBAction)captureID:(UIButton *)sender
{
	ConfirmCapture.singleton.delegate = self;
	[self presentViewController:ConfirmCapture.singleton.controller animated:YES completion:^{

	}];
}
```

Write delegate methods to receive the imagery and payload data from the capture experience:

```obj-c
- (void)ConfirmCaptureDidComplete:(ConfirmPayload *)payload
{
	[ConfirmSubmit.singleton submitIDCapturePayload:payload onStatus:^(NSDictionary * _Nonnull info, ConfirmSubmitState state) {
        // Available ConfirmSubmitState values:
        // - ConfirmSubmitStateInitializing
		// - ConfirmSubmitStateUploading
		// - ConfirmSubmitStateReceivedGuid
		// - ConfirmSubmitStateProcessing
		// - ConfirmSubmitStateGettingResults
		// - ConfirmSubmitStateCompleted
    } onProgress:^(NSProgress * _Nonnull progress, ConfirmSubmitProgressType progressType) {
        // Available ConfirmSubmitProgressTypes:
        // - ConfirmSubmitUploadProgress (ID is being uploaded to Confirm's cloud)
		// - ConfirmSubmitDownloadProgress (ID is being processed by Confirm's cloud)
    } onSuccess:^(IDModel * _Nullable validatedID) {
        // Fully parsed and processed ID is available in the `validatedID` object
    } onError:^(NSError * _Nonnull error, NSString * _Nullable guid) {
        // An error occurred with the API request. Often due to a missing or invalid API key.
    }];
}

- (void)ConfirmCaptureDidCancel
{
	// ...handle capture view dismissal 
}
```

### Delegate methods

There are two delegate calls that the client can receive while using `ConfirmCapture`:

##### - (void)ConfirmCaptureDidComplete:(ConfirmPayload *)payload

The first delegate call is the method that occurs after the capture has completed. When your ViewController receives this call, the `payload` object will contain all the information needed to leverage `ConfirmSubmit` and send the data to Confirm's cloud. Developers should retain this payload until they're ready to execute the submission.

##### - (void)ConfirmCaptureDidCancel

The second delegate call is the method that occurs when the user has backed out of the capture experience without capturing their ID. Developers are welcome to trigger different workflows or retry the capture experience as they see fit.

### Facial matching (compare face on ID to selfie)

In addition to capturing and authenticating identity documents, Confirm partners with MorphoTrust USA to provide facial comparison technology. Combining document authentication with facial matching brings trust in identity to a whole new level by authenticating legitimacy of documentation as well as legitimacy of ownership. 

In order to include facial matching to your workflow, simply ensure that the `ConfirmCapture` singleton has the variable `enableFacialMatch` set to true before presenting the controller:

```obj-c
- (IBAction)captureID:(UIButton *)sender
{
	ConfirmCapture.singleton.delegate = self;
	ConfirmCapture.singleton.enableFacialMatch = true;
	[self presentViewController:ConfirmCapture.singleton.controller animated:YES completion:^{

	}];
}
```

With facial match enabled, the selfie capture view will be appended to the capture workflow, and the `ConfirmPayload` will include the facial image required for `ConfirmSubmit` to execute the facial match request. 

### Submit to Confirm.io's API

After both the front and back of the ID have been captured, the payload can then be sent to Confirm.io's cloud API for data extraction and authentication. 

Before submission to the Confirm API, developers must obtain an API key from Confirm's team directly. It is highly recommended that mobile developers leverage Confirm's consumer key authentication protocols when submitting images directly to Confirm's API. To learn more, [please visit our documentation](https://confirm.readme.io/docs/authentication).

The code containing verification API is located in the object `ConfirmSubmit`.

To set the API key:

```obj-c
ConfirmSubmit.singleton.apiKey = @"{YOUR_API_KEY_HERE}";
```

_A good place for this initialization is in the UIApplication delegate method `application:didFinishLaunchingWithOptions:`,  but it can be made anywhere prior to the actual ConfirmSubmit API call._

Once you have the payload captured via `ConfirmCapture`, the developer now needs to submit those images to the Confirm.io API for authentication:

```obj-c
- (void)submit
{
	self.session = [ConfirmSubmit.singleton submitIDCapturePayload:payload onStatus:^(NSDictionary * _Nonnull info, ConfirmSubmitState state) {
        // Available ConfirmSubmitState values:
        // - ConfirmSubmitStateInitializing
		// - ConfirmSubmitStateUploading
		// - ConfirmSubmitStateReceivedGuid
		// - ConfirmSubmitStateProcessing
		// - ConfirmSubmitStateGettingResults
		// - ConfirmSubmitStateCompleted
    } onProgress:^(NSProgress * _Nonnull progress, ConfirmSubmitProgressType progressType) {
        // Available ConfirmSubmitProgressTypes:
        // - ConfirmSubmitUploadProgress (ID is being uploaded to Confirm's cloud)
		// - ConfirmSubmitDownloadProgress (ID is being processed by Confirm's cloud)
    } onSuccess:^(IDModel * _Nullable validatedID) {
        // Fully parsed and processed ID is available in the `validatedID` object
    } onError:^(NSError * _Nonnull error, NSString * _Nullable guid) {
        // An error occurred with the API request. Often due to a missing or invalid API key.
    }];
}
```

#### Return value
The `ConfirmSession` object returned can be used at any time prior to the `onSuccess` or `onError` blocks get called to cancel the transaction.

This can simply be done by a standard

```obj-c
- (IBAction)didTapCancelButton:(UIButton*)sender
{
	[self.session cancel];
	self.session = nil;
}
```

*NOTE*: Since network calls are taking place, the blocks will be called asynchronously at some later time, so the developer would most likely want to block user interface in some manner - most likely to not make successive calls to `submitIDCapturePayload:(ConfirmPayload* _Nonnull)payload onStatus:(_Nullable ConfirmSubmitStatusCallback)statusBlock onProgress:(_Nullable ConfirmSubmitProgressCallback)progressBlock onSuccess:(_Nullable ConfirmSubmitResultCallback)successBlock onError:(_Nullable ConfirmSubmitErrorCallback)errorBlock` before the first call has a chance to complete. This can easily be done by setting the parent view's `userInteractionEnabled` to NO before the call, and to YES on either success or error.

##### onStatus:

This block will be called at various state transitions, and has an `NSDictionary` containing helpful, human readible strings to indicate the progress of the various states.

Once the ID's serve GUID is available, it will also become available in the `kStatusInfoGuidKey` key of the info parameter.

##### onProgress:

This block will be called during network upload and download progress. It will return an NSProgress object that can be inspected for data transmission `completedUnitCount` and `totalUnitCount`, and also an enumerated type indicating whether it is an upload or download progress event.

##### onSuccess:

This block will be called if all the network calls succeed and API returns with an authentication result. The ID information will be contained in the `IDModel` data structure called `validatedID`. No more block calls will be made after this block is received.

##### onError:

This block will be called if there was a network or authentication error with the request. The error as to what happened will be provided in the `NSError`, and no more block calls will be made after this block is received.
