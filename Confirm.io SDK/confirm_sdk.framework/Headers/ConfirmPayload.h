//
//  ConfirmPayload.h
//  confirm-sdk
//
//  Created by roy on 4/21/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef void (^ConfirmPayloadFetchImage)(UIImage* image);

@interface ConfirmPayload : NSObject

@property (nonatomic, readonly) UIImage*	licenseCroppedImage;
@property (nonatomic, readonly) UIImage*	selfieCroppedImage; 

@property (nonatomic, readonly) UIImage*	frontImage; 
@property (nonatomic, readonly) UIImage*	backImage; 
@property (nonatomic, readonly) UIImage*	selfieImage; 

@property (nonatomic, readonly) BOOL		hasSelfie;

- (void)cleanup;

+ (instancetype)payload;

- (void)fetchFrontImage:(ConfirmPayloadFetchImage)fetchBlock;
- (void)fetchBackImage:(ConfirmPayloadFetchImage)fetchBlock;
- (void)fetchSelfieImage:(ConfirmPayloadFetchImage)fetchBlock;

@end
