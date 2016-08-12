//
//  IDImagesModel.h
//  AIDD Demo App
//
//  Created by David Thor on 8/19/15.
//  Copyright (c) 2015 AIDD. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface IDImagesModel : NSObject

@property (nonatomic, retain) NSString *front;
@property (nonatomic, retain) NSString *back;

+ (instancetype)model;
+ (instancetype)modelWithResponse:(NSDictionary*)responseObject;

@end
