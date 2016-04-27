//
//  IdentityBio.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IdentityBioModel : NSObject

@property (nonatomic, retain, readonly) NSString *firstName;
@property (nonatomic, retain, readonly) NSString *middleName;
@property (nonatomic, retain, readonly) NSString *lastName;
@property (nonatomic, retain, readonly) NSString *address;
@property (nonatomic, retain, readonly) NSString *city;
@property (nonatomic, retain, readonly) NSString *state;
@property (nonatomic, retain, readonly) NSString *zip;
@property (nonatomic, retain, readonly) NSString *country;
@property (nonatomic, retain, readonly) NSDate   *dob;
@property (nonatomic, readonly) 		NSInteger age;
@property (nonatomic, retain, readonly) NSString *gender;
@property (nonatomic, retain, readonly) NSString *height;
@property (nonatomic, retain, readonly) NSString *weight;

+ (instancetype)model;
+ (instancetype)modelWithResponse:(NSDictionary*)responseObject;

@end
