//
//  MTDigitalWatermark_LicenseKey.h
//  MTDigitalWatermark
//
//  Created by clayton on 8/18/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MTDigitalWatermark_LicenseKey : NSObject

+ (instancetype)alloc __attribute__((unavailable("This method is not available")));
- (instancetype)init __attribute__((unavailable("This method is not available")));
+ (instancetype)new __attribute__((unavailable("This method is not available")));
+ (instancetype)copy __attribute__((unavailable("This method is not available")));

+(void)setLicense:(NSString *)key error:(NSError **)error;

+(BOOL)licenseValid;
+(NSDate *)licenseExpirationDate;



@end
