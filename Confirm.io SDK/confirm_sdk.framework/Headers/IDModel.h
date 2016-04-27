//
//  IDModel.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "IDImagesModel.h"
#import "IdentityModel.h"

@interface IDModel : NSObject

@property (readonly) BOOL isPending;
@property (readonly) BOOL isUnknown;
@property (readonly) BOOL didPass;
@property (readonly) BOOL didFail;

@property (nonatomic, retain, readonly) NSString *		guid;
@property (nonatomic, retain, readonly) NSDate*	 		submittedOn;
@property (nonatomic, retain, readonly) NSDate* 		updatedOn;
@property (nonatomic, retain, readonly) NSDate* 		processingCompletedOn;
@property (nonatomic, retain, readonly) IDImagesModel*	images;
@property (nonatomic, retain, readonly) IdentityModel*	identity;

+ (instancetype)model;
+ (instancetype)modelWithResponse:(NSDictionary*)responseObject;

@end
