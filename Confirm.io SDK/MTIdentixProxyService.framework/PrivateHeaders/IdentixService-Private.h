//
//  IdentixService-Private.h
//  MTIdentixProxyService
//
//  Created by Michael Callaghan on 2/11/16.
//  Copyright © 2016 Morphotrust. All rights reserved.
//

#import <MTIdentixProxyService/IdentixService.h>

@interface IdentixService()

typedef NS_ENUM(NSInteger, DocAuthStrategy) {
	DocAuthStrategyDeep,
	DocAuthStrategyFast
};

@property (nonatomic, strong) NSString *identixURL;

/*!
 * @discussion This function is used to authenticate and extract information from a driver license.
 @param cardFrontImage An instance of IdentixImage that contains the image of a driver license and the desired compression quality.
 @param cardBackImage This parameter is not currently being used and should be set to nil.
 @param strategy The strategy of the document authentication to use. Deep uses MorphoTrust's document authentication capability while Fast uses a partner's document authentication capability.
 @param success A block that if executed will return a DocAuthVerifyResponse object called success. This success object will include the status and response in JSON format among other values.
 @param error A block that if executed will return an NSError object called error.
 */
- (void)docAuthVerify:(IdentixImage *)cardFrontImage backImage:(IdentixImage *)cardBackImage ofType:(DocAuthStrategy)strategy onSuccess:(void (^)(DocAuthVerifyResponse *))success onError:(void (^)(NSError *))error;

@end
