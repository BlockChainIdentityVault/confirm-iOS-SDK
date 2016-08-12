//
//  FaceFeatures.h
//  MTImage
//
//  Created by clayton on 6/22/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

/*!
 * @brief These are the features of a face that have been detected in an image after calling the getFaceFeaturesWithAccuracy function.
 */
typedef struct
{
    CGRect bounds;
    CGPoint leftEye;
    CGPoint rightEye;
    CGPoint mouth;
    float faceAngle;
    BOOL smile;
    BOOL leftEyeBlinking;
    BOOL rightEyeBlinking;
    int featureCount;
} FaceFeatures;

/*!
 * @brief The accuracy at which the client would like to detect a face inside of an image. There are only two available options- HighAccuracy and LowAccuracy.
 */
typedef enum FaceDetectionAccuracy: NSInteger
{
    LowAccuracy,
    HighAccuracy
} FaceDetectionAccuracy;