//
//  ConfirmCameraDemo.h
//  Sample
//
//  Created by roy on 5/11/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <UIKit/UIKit.h>

@class ConfirmPayload;

@interface ConfirmCameraDemo : NSObject

+ (ConfirmCameraDemo*)singleton;

- (void)runDemo:(UIViewController*)parent completion:(void(^)(ConfirmPayload* payload))completion;

@end
