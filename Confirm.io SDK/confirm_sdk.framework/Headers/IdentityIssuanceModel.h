//
//  IdentityIssuance.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IdentityIssuanceModel : NSObject

@property (nonatomic, retain) NSString *number;
@property (nonatomic, retain) NSDate *issued;
@property (nonatomic, retain) NSDate *expiration;

+ (instancetype)model;

@end
