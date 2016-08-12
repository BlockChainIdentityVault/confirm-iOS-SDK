//
//  IdentixService.h
//
//  Created by Clayton Gragg on 11/11/15.
//  Copyright © 2015 Morphotrust. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <AFNetworking/AFNetworking.h>

#import "DocAuthVerifyResponse.h"
#import "FaceVerifyResponse.h"
#import "IdentixImage.h"

@interface IdentixService : NSObject

/*!
 * @discussion This initializer must be used to create an instance of an IdentixService object.
   @param apiKey A key provided by MorphoTrust. This key will enable access to the Identix service in order to perform biometric facial matching and driver license document authentication.
   @param url The Identix service URL provided to you by MorphoTrust.
 */
- (id)initWithAPIKey:(NSString *)apiKey identixURL:(NSString *)url;

/*!
 * @discussion This function is used to match two faces. For instance, this function can be used to compare a selfie with the portrait extracted from a driver license.
   @param faceImage1 An instance of IdentixImage that contains the image of a face and the desired compression quality.
   @param faceImage2 An instance of IdentixImage that contains the image of a face and the desired compression quality.
   @param success A block that if executed will return a FaceVerifyResponse object called success. This success object will include the match score among other values.
   @param error A block that if executed will return an NSError object called error.
 */
- (void)faceVerify:(IdentixImage *)faceImage1 andImage:(IdentixImage *)faceImage2 onSuccess:(void (^)(FaceVerifyResponse *))success onError:(void (^)(NSError *))error;

/*!
 * @discussion This function is used to authenticate and extract information from a driver license.
 @param cardFrontImage An instance of IdentixImage that contains the image of a driver license and the desired compression quality.
 @param success A block that if executed will return a DocAuthVerifyResponse object called success. This success object will include the status and response in JSON format among other values.
 @param error A block that if executed will return an NSError object called error.
 */
- (void)docAuthVerify:(IdentixImage *)cardFrontImage onSuccess:(void (^)(DocAuthVerifyResponse *))success onError:(void (^)(NSError *))error;

@end


