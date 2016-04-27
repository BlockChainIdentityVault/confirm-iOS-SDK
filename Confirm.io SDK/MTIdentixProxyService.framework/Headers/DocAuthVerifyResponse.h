//
//  DocAuthVerifyResponse.h
//  MTIdentixProxyService
//
//  Created by clayton on 11/18/15.
//  Copyright © 2015 Morphotrust. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DocAuthVerifyResponse : NSObject {
	
}

/*!
 * @brief Information pertaining specifically to the document.
 */
@property (nonatomic, strong, readonly) NSDictionary *folioDocument;
/*!
 * @brief Whether tests passed, failed, or were indeterminate. If no test fails then the status will be passed.
 */
@property (nonatomic, strong, readonly) NSString *status;
/*!
 * @brief Tests performed on the document including scanning for a watermark.
 */
@property (nonatomic, strong, readonly) NSDictionary *tests;
/*!
 * @brief Personal information extracted from the document.
 */
@property (nonatomic, strong, readonly) NSDictionary *folioPerson;
/*!
 * @brief Measurement of how long the request took.
 */
@property (nonatomic, strong, readonly) NSString *networkingTimeInterval;
/*!
 * @brief Response in JSON format.
 */
@property (nonatomic, strong, readonly) NSDictionary *responseJSON;

@end


