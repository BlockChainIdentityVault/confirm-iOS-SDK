//
//  ConfirmCapture.h
//  confirm-sdk
//
//  Created by roy on 4/7/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@class ConfirmPayload;

@protocol ConfirmCaptureDelegate <NSObject>

- (void)ConfirmCaptureDidComplete:(ConfirmPayload*)payload;
- (void)ConfirmCaptureDidCancel;

@end

@interface ConfirmCapture : NSObject

@property (nonatomic, assign)		id<ConfirmCaptureDelegate>	delegate;
@property (nonatomic, assign)		BOOL						enableFacialMatch;

+ (ConfirmCapture*)singleton;

- (UINavigationController*)confirmController;

// deletes cached images, etc.
- (void)cleanup;	

@end
