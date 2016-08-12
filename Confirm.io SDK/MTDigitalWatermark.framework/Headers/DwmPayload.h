//
//  DwmPayload.h
//  MTDigitalWatermark
//
//  Created by clayton on 6/12/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface DwmPayload : NSObject

@property (nonatomic, strong) NSString *docNumber;
@property (nonatomic, strong) NSString *issuer;
@property (nonatomic, strong) NSString *docType;
@property (nonatomic, strong) NSString *dob;
@property (nonatomic) int iDay;
@property (nonatomic) int iMonth;
@property (nonatomic) int iYear;

//quality measures
@property (nonatomic) double overall;
@property (nonatomic) double lighting;

//stats
@property (nonatomic) float pStrength;
@property (nonatomic) float sStrength;
@property (nonatomic) float pRotation;
@property (nonatomic) float sRotation;
@property (nonatomic) float primaryScale;
@property (nonatomic) float secondaryScale;
@property (nonatomic) BOOL valid;

//individual payload fields
@property (nonatomic, strong) NSString *pDocNumber;
@property (nonatomic, strong) NSString *pIssuer;
@property (nonatomic, strong) NSString *pDocType;
@property (nonatomic, strong) NSString *sDocNumber;
@property (nonatomic, strong) NSString *sIssuer;
@property (nonatomic, strong) NSString *sDocType;

@end
