//
//  DocAuthVerifyResponse-Private.h
//  MTIdentixProxyService
//
//  Created by Michael Callaghan on 2/11/16.
//  Copyright © 2016 Morphotrust. All rights reserved.
//

#import <MTIdentixProxyService/DocAuthVerifyResponse.h>

#define MT_DOCAUTH_RESPONSE_TESTS_ESF_KEY				"Watermark"
#define MT_DOCAUTH_RESPONSE_TESTS_OCR_KEY				"Misc"

#define MT_DOCAUTH_RESPONSE_TEST_RESULT_KEY				"result"

#define MT_DOCAUTH_RESPONSE_TEST_RESULT_PASSED_VALUE	"Passed"
#define MT_DOCAUTH_RESPONSE_TEST_RESULT_FAILED_VALUE	"Failed"
#define MT_DOCAUTH_RESPONSE_TEST_RESULT_INDETERMINATE_VALUE	"Indeterminate"

#define MT_DOCAUTH_FOLIOPERSON_ADDRESSES_KEY			"addresses"

#define MT_DOCAUTH_FOLIOPERSON_ADDRESSES_ZIP_KEY		"zip"

#define MT_DOCAUTH_FOLIOPERSON_NAME_KEY					"name"

#define MT_DOCAUTH_FOLIOPERSON_NAME_FIRSTNAME_KEY		"givenName"
#define MT_DOCAUTH_FOLIOPERSON_NAME_LASTNAME_KEY		"surName"

@interface DocAuthVerifyResponse()

- (id)initWithData:(NSDictionary *)data andTimeInterval:(NSString *)timeInterval;
- (id)initWithStatus:(NSString *)status;

- (void)setStatus:(NSString *)status;
- (void)setNetworkingTimeInterval:(NSString *)networkingTimeInterval;
- (void)setResponseJSON:(NSDictionary *)responseJSON;

- (NSString *)getFolioPersonFirstName;
- (NSString *)getFolioPersonLastName;
- (NSString *)getFolioPersonZIP;
- (NSString *)getOCRTestResultJSON;

@end
