//
//  InterstitialVC.h
//  Sample
//
//  Created by roy on 5/11/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface InterstitialVC : UIViewController

+ (InterstitialVC*)controller:(NSString*)message completion:(void(^)(BOOL next))completion;

@end
