//
//  ConfirmSession.h
//  confirm-sdk
//
//  Created by roy on 2/29/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface ConfirmSession : NSObject

- (void)cancel;
- (void)pause;
- (void)resume;

@end
