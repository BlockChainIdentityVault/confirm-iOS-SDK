//
//  ConfirmSubmit.h
//  confirm-sdk
//
//  Created by roy on 1/20/16.
//  Copyright © 2016 confirm.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@class IDModel;

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
	ConfirmSubmitStateCompleted
} ConfirmSubmitState;

NS_ASSUME_NONNULL_BEGIN

FOUNDATION_EXPORT NSString * const kConfirmSubmitErrorDomain;
NS_ENUM(NSInteger)
{
	kConfirmSubmitErrorNoAPIKey		= -4000,
	kConfirmSubmitErrorBadAPIKey	= -4001,
	kConfirmSubmitErrorHTTPErrKey	= -4002,
	
};

FOUNDATION_EXPORT NSString * const kStatusInfoTitleKey;			// value: NSString*
FOUNDATION_EXPORT NSString * const kStatusInfoMessageKey;		// value: NSString*
FOUNDATION_EXPORT NSString * const kStatusInfoGuidKey;			// value: NSString*

NS_ASSUME_NONNULL_END

typedef void (^ConfirmSubmitStatusCallback)(NSDictionary* _Nonnull info, ConfirmSubmitState state);
typedef void (^ConfirmSubmitProgressCallback)(NSProgress* _Nonnull progress, ConfirmSubmitProgressType progressType);
typedef void (^ConfirmSubmitResultCallback)(IDModel* _Nullable validatedID);
typedef void (^ConfirmSubmitErrorCallback)(NSError* _Nonnull error, NSString* _Nullable guid);


@interface ConfirmSubmit : NSObject

@property (nonatomic, retain)	NSString* _Nonnull apiKey;

+ (ConfirmSubmit* _Nonnull)singleton;

- (void)submitIDWithFrontImage:(UIImage * _Nonnull)frontImage 
				  andBackImage:(UIImage * _Nullable)backImage 
					  onStatus:(_Nullable ConfirmSubmitStatusCallback)statusBlock
					onProgress:(_Nullable ConfirmSubmitProgressCallback)progressBlock
					 onSuccess:(_Nullable ConfirmSubmitResultCallback)successBlock 
					   onError:(_Nullable ConfirmSubmitErrorCallback)errorBlock;

+ (void)cleanup;

@end
