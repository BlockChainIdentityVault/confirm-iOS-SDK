//
//  ConfirmSubmit.h
//  confirm-sdk
//
//  Created by roy on 1/20/16.
//  Copyright © 2016 confirm.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@class IDModel;
@class FacialMatchResponse;
@class ConfirmSession;
@class ConfirmPayload;


typedef enum {
	ConfirmSubmitUploadProgress,
	ConfirmSubmitDownloadProgress,
} ConfirmSubmitProgressType;

typedef enum {
	ConfirmSubmitStateInitializing,
	ConfirmSubmitStateUploading,
	ConfirmSubmitStateReceivedGuid,
	ConfirmSubmitStateProcessing,
	ConfirmSubmitStateGettingResults,
	ConfirmSubmitStateCancelling,
	ConfirmSubmitStateCancelled,
	ConfirmSubmitStateCompleted
} ConfirmSubmitState;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const kConfirmSubmitErrorDomain;
NS_ENUM(NSInteger)
{
	kConfirmSubmitErrorNoAPIKey		= -4000,
	kConfirmSubmitErrorBadAPIKey	= -4001,
	kConfirmSubmitErrorHTTPErrKey	= -4002,
	kConfirmSubmitErrorCancelled	= -4003
	
};

FOUNDATION_EXPORT NSString * const kStatusInfoTitleKey;			// value: NSString*
FOUNDATION_EXPORT NSString * const kStatusInfoMessageKey;		// value: NSString*
FOUNDATION_EXPORT NSString * const kStatusInfoGuidKey;			// value: NSString*

NS_ASSUME_NONNULL_END

typedef void (^ConfirmSubmitStatusCallback)(NSDictionary* _Nonnull info, ConfirmSubmitState state);
typedef void (^ConfirmSubmitProgressCallback)(NSProgress* _Nonnull progress, ConfirmSubmitProgressType progressType);
typedef void (^ConfirmSubmitResultCallback)(IDModel* _Nullable validatedID);
typedef void (^ConfirmSubmitPayloadResultCallback)(IDModel * _Nullable validatedID, FacialMatchResponse * _Nullable facialResponse);
typedef void (^ConfirmSubmitErrorCallback)(NSError* _Nonnull error, NSString* _Nullable guid);
typedef void (^ConfirmSubmitLightAuthResultCallback)(NSDictionary* _Nonnull info);
typedef void (^ConfirmSubmitLightAuthErrorCallback)(NSError* _Nonnull error, NSInteger statusCode);

@interface ConfirmSubmit : NSObject

@property (nonatomic, retain)	NSString* _Nonnull	apiKey;
@property (nonatomic, assign)	float				facialMatchThreshold;

+ (ConfirmSubmit* _Nonnull)singleton;

- (nullable ConfirmSession*)submitBarcodeData:(NSString* _Nonnull)barcode
									onSuccess:(_Nonnull ConfirmSubmitResultCallback)successBlock
									  onError:(_Nonnull ConfirmSubmitLightAuthErrorCallback)errorBlock;

- (nullable ConfirmSession*)submitIDCapturePayload:(ConfirmPayload* _Nonnull)payload
										  onStatus:(_Nullable ConfirmSubmitStatusCallback)statusBlock
										onProgress:(_Nullable ConfirmSubmitProgressCallback)progressBlock
										 onSuccess:(_Nonnull ConfirmSubmitPayloadResultCallback)successBlock
										   onError:(_Nonnull ConfirmSubmitErrorCallback)errorBlock;

+ (void)cleanup;

// MorphoTrust

- (void)setMorphoTrustAPIKey:(NSString* _Nonnull)apiKey andURL:(NSString* _Nonnull)url;
- (void)setMorphoTrustDWMKey:(NSString* _Nonnull)dwmKey;

@end
