//
//  MorphoSelfieVC.h
//  confirm-sdk
//
//  Created by roy on 7/18/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <UIKit/UIKit.h>

@protocol MorphoSelfieDelegate

- (void)morphoCancelled;
- (void)morphoCaptured:(UIImage*)image;

@end

@interface MorphoSelfieVC : UIViewController

@property (nonatomic, assign) id<MorphoSelfieDelegate> delegate;

+ (MorphoSelfieVC*)controller;

@end
