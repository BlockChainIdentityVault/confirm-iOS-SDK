//
//  ViewController.swift
//  SwiftSample
//
//  Created by roy on 8/3/16.
//  Copyright © 2016 confirm.io. All rights reserved.
//

import UIKit
import confirm_sdk

class ViewController: UIViewController, ConfirmCaptureDelegate {
	
	@IBOutlet weak var checkIDButton: UIButton!
	@IBOutlet weak var checkIDSelfieButton: UIButton!
	@IBOutlet weak var statusLabel: UILabel!
	@IBOutlet weak var progressLabel: UILabel!
	
	var payload: ConfirmPayload!
	var lastProgress: NSTimeInterval = 0
	
	
	override func viewDidLoad() 
	{
		super.viewDidLoad()
	}
	
	@IBAction func didTapCheckID(sender: UIButton)
	{
		var cc: ConfirmCapture
		var nav: UINavigationController
		
		cc = ConfirmCapture.singleton()
		nav = cc.confirmController()
		
		cc.delegate = self
		cc.enableFacialMatch = false
		
		self.presentViewController(nav, animated: true, completion: nil)
		
		self.checkIDButton.enabled = false
		self.checkIDSelfieButton.enabled = false
		self.setStatusString("")
		self.setProgressString("")
	}
	
	@IBAction func didTapCheckIDSelfie(sender: UIButton)
	{
		var cc: ConfirmCapture
		var nav: UINavigationController
		
		cc = ConfirmCapture.singleton()
		nav = cc.confirmController()
		
		cc.delegate = self
		cc.enableFacialMatch = true
		self.presentViewController(nav, animated: true, completion: nil)
		
		self.checkIDButton.enabled = false
		self.checkIDSelfieButton.enabled = false
		self.setStatusString("")
		self.setProgressString("")
	}
	
	func setProgressString(value: NSString)
	{
		NSOperationQueue.mainQueue().addOperationWithBlock { 
			self.progressLabel.text = value as String
		}
	}
	
	func setStatusString(value: NSString)
	{
		NSOperationQueue.mainQueue().addOperationWithBlock { 
			self.statusLabel.text = value as String
		}
	}
	
	
	func ConfirmCaptureDidComplete(payload: ConfirmPayload)
	{
		ConfirmSubmit.singleton().submitIDCapturePayload(payload,
		                                                 onStatus: { (info_: Dictionary, state: ConfirmSubmitState) in
															let info: NSDictionary = info_ as NSDictionary
															let blurb_: AnyObject? = info[kStatusInfoTitleKey]
															var blurb: NSString = "";
															
															if blurb_ != nil {
																blurb = blurb_ as! NSString
																let message_: AnyObject? = info[kStatusInfoMessageKey]
																
																if message_ != nil {
																	let message: NSString = message_ as! NSString
																	blurb = blurb.stringByAppendingFormat("\n%@", message)
																}
															}
															let guid_ : AnyObject? = info[kStatusInfoGuidKey];
															
															if guid_ != nil {
																let guid: NSString = guid_ as! NSString;
																blurb = NSString.localizedStringWithFormat("\nguid received:\n%@", guid)
															}
															self.setStatusString(blurb);
														},
		                                                 onProgress:{ (progress: NSProgress, progressType: ConfirmSubmitProgressType) in
															let rightNow: NSTimeInterval = CACurrentMediaTime()
															
															if progress.completedUnitCount == progress.totalUnitCount {
																self.setProgressString("Sample App")
															} else if rightNow-self.lastProgress > 1.0 {	// throttle progress to every second
																let blurb: NSString = NSString.localizedStringWithFormat("%@ %@ out of %@",
																	progressType == ConfirmSubmitUploadProgress ? "Uploading" : "Downloading",
																	self.memoryString(progress.completedUnitCount)!,
																	self.memoryString(progress.totalUnitCount)!)
																
																self.setProgressString(blurb)
																self.lastProgress = rightNow
															}
														},
		                                                 onSuccess:{ (validatedID, facialResponse) in
															self.showResults(validatedID, facialResponse:facialResponse)
															ConfirmCapture.singleton().cleanup()
															self.payload = nil
															self.checkIDButton.enabled = true;
															self.checkIDSelfieButton.enabled = true;
														}, 
		                                                 onError:{ (error, guid) in
															NSLog("submission error\n%@", error.localizedDescription)
															ConfirmCapture.singleton().cleanup()
															self.payload = nil
															self.checkIDButton.enabled = true;
															self.checkIDSelfieButton.enabled = true;
														}
		)
		
		self.finishIDCapture()
	}
	
	func ConfirmCaptureDidCancel()
	{
		self.finishIDCapture()
	}
	
	func finishIDCapture()
	{
		self.dismissViewControllerAnimated(true, completion:nil)
	}
	
	func showResults(validatedID: IDModel?, facialResponse: FacialMatchResponse?)
 	{
		if validatedID != nil {
			var status: NSString = ""
			if validatedID!.didPass {
				status = "ID passed";
			} else if validatedID!.didFail {
				status = "ID failed";
			} else if validatedID!.isUnknown {
				status = "ID unknown"
			}
			let identity: IdentityModel = validatedID!.identity
			let classification: IdentityClassificationModel = identity.classification;
			let issuance: IdentityIssuanceModel = identity.issuance
			let bio: IdentityBioModel = identity.bio
			
			status = status.stringByAppendingFormat(" (%@ %@ %@)\n%@ %@", classification.state, classification.type, issuance.number,
			                                        bio.firstName, bio.lastName	);
			self.setStatusString(status)
		}
		
		if facialResponse != nil {
			var progress: String = "";
			switch facialResponse!.facialMatchValue {
				case FacialMatchValueUnknown:
					progress = "FacialMatch: unknown"
					break
				case FacialMatchValueFailed:
					progress = "FacialMatch: failed"
					break
				case FacialMatchValuePassed:
					progress = "FacialMatch: passed"
					break
				case FacialMatchValueError:
					progress = "FacialMatch: error"
					break
				default: break
			}
			self.setProgressString(progress)
		}
	}
	
	func memoryString(value: Int64) -> NSString?
	{
		var dval: Double = Double(value)
		
		if dval < 1024 {
			return NSString.localizedStringWithFormat("%d B", dval)
		} else {
			dval /= 1024.0
			if dval < 1024 {
				return NSString.localizedStringWithFormat("%0.1f KB", dval)
			} else {
				dval /= 1024.0
				if dval < 1024 {
					return NSString.localizedStringWithFormat("%0.1f MB", dval)
				} else {
					dval /= 1024.0
					if dval < 1024 {
						return NSString.localizedStringWithFormat("%0.1f GB", dval)
					} else {
						dval /= 1024.0
						if dval < 1024 {
							return NSString.localizedStringWithFormat("%0.1f TB", dval)
						}
					}
				}
			}
		}
		return nil
	}
}

