//
//  EmbeddedVC.h
//  Sample
//
//  Created by roy on 5/17/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol EmbeddedDelegate < NSObject >

- (void)embededFinished;

@end

@interface EmbeddedVC : UIViewController
@property (nonatomic, weak) id<EmbeddedDelegate> delegate;

+ (EmbeddedVC*)controller;

@end
