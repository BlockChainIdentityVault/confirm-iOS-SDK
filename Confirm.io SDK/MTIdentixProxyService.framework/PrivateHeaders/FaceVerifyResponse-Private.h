//
//  FaceVerifyResponse-Private.h
//  MTIdentixProxyService
//
//  Created by Chris Poole on 1/26/16.
//  Copyright © 2016 Morphotrust. All rights reserved.
//

#import <MTIdentixProxyService/FaceVerifyResponse.h>

@interface FaceVerifyResponse()

@property (nonatomic, strong) NSDictionary *responseJSON;

- (id)initWithData:(NSDictionary *)data andTimeInterval:(NSString *)timeInterval;

- (void)setStatus:(NSString *)status;

@end
