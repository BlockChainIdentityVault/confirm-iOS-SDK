//
//  IdentityClassification.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IdentityClassificationModel : NSObject

@property (nonatomic, retain) NSString *type;
@property (nonatomic, retain) NSString *state;

+ (instancetype)model;

@end
