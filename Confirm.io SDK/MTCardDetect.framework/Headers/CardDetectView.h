//
//  CardDetectView.h
//  MTCardDetect
//
//  Created by clayton on 10/30/15.
//  Copyright © 2015 MorphoTrust. All rights reserved.
//

//Card Detect Delegate functions
@protocol cardDetectDelegate <NSObject>

@required
/*!
 * @discussion This delegate protocol is fired when the DWM detection process is completed (either by time out or successful detection of DWM data). This delegate function is required.
 @param image The payload object that contains the parsed ESF data.
 */
-(void)detectCompleted:(UIImage *)image;

@optional
/*!
 * @discussion This delegate protocol is fired when the library encounters an error attempting to decode the ESF. This delegate function is optional.
 @param message A string description of an error that took place during attempted detection.
 */
-(void)detectError:(NSString *)message;

@end

//SDK interface
@interface CardDetectView : UIView

/*!
 * @brief In order for cardDetectDelegate functions to work properly in the client app, this property must be set to self.
 */
@property (nonatomic, weak) id<cardDetectDelegate> delegate;

/*!
 * @brief When saveEnergy is set to True the library will stop the video camera after each DWM detection.  This conserves battery life on the phone.  The drawback is that each time the video camera is started there is a focus adjustment which can make rapid scanning of ESFs slower. Default value is True.
 */
@property (nonatomic) BOOL saveEnergy;

/*!
 * @discussion This function starts the video feed (using the rear camera) and displays the video feed. The function searches the video frames for the presense of a DWM.  Once detected, the DWM data is parsed to the MorphoTrust specifications for US Driver’s Licenses.  The parsed data is returned using the delegate callback detectCompleted.
     @param maxDurationInSeconds Indicates how long to analyze the video frames for an ESF/DWM before timing out.
 */
-(void)startDetect:(int)maxDurationInSeconds;

/*!
 * @discussion This function forcibly stops the detection method.
 */
-(void)stopDetect;

@end

