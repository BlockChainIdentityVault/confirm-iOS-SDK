//
//  IdentityModel.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IdentityClassificationModel.h"
#import "IdentityIssuanceModel.h"
#import "IdentityBioModel.h"

@interface IdentityModel : NSObject

@property (nonatomic, retain) IdentityClassificationModel *classification;
@property (nonatomic, retain) IdentityIssuanceModel *issuance;
@property (nonatomic, retain) IdentityBioModel *bio;

+ (instancetype)model;
+ (instancetype)modelWithResponse:(NSDictionary*)responseObject;

@end
