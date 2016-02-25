//
//  IdentityBio.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IdentityBioModel : NSObject

@property (nonatomic, retain) NSString *firstName;
@property (nonatomic, retain) NSString *middleName;
@property (nonatomic, retain) NSString *lastName;
@property (nonatomic, retain) NSString *address;
@property (nonatomic, retain) NSString *city;
@property (nonatomic, retain) NSString *state;
@property (nonatomic, retain) NSString *zip;
@property (nonatomic, retain) NSString *country;
@property (nonatomic, retain) NSDate   *dob;
@property (nonatomic, assign) NSInteger age;
@property (nonatomic, retain) NSString *gender;
@property (nonatomic, retain) NSString *height;
@property (nonatomic, retain) NSString *weight;

+ (instancetype)model;

@end
