//
//  FacialMatchResponse.h
//  confirm-sdk
//
//  Created by roy on 4/27/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef enum {
	FacialMatchValueUnknown,
	FacialMatchValueFailed,
	FacialMatchValuePassed,
	FacialMatchValueError
} FacialMatchValue;

@class FaceVerifyResponse;

@interface FacialMatchResponse : NSObject

@property (readonly) FacialMatchValue	facialMatchValue;
@property (readonly) float				facialMatchScore;

@end
