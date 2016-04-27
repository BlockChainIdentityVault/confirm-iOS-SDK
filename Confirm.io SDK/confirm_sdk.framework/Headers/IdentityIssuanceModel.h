//
//  IdentityIssuance.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IdentityIssuanceModel : NSObject

@property (nonatomic, retain, readonly) NSString *	number;
@property (nonatomic, retain, readonly) NSDate *	issued;
@property (nonatomic, retain, readonly) NSDate *	expiration;

+ (instancetype)model;
+ (instancetype)modelWithResponse:(NSDictionary*)responseObject;

@end
