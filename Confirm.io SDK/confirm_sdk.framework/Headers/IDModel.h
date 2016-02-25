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

@property (nonatomic, retain) NSString *		guid;
@property (nonatomic, retain) NSString *		status;
@property (nonatomic, retain) NSDate*	 		submittedOn;
@property (nonatomic, retain) NSDate* 			updatedOn;
@property (nonatomic, retain) NSDate* 			processingCompletedOn;
@property (nonatomic, retain) IDImagesModel *	images;
@property (nonatomic, retain) IdentityModel *	identity;

+ (instancetype)model;

+ (instancetype)testModel;

@end
