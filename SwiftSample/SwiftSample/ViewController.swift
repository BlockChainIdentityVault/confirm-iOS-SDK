//
//  ViewController.swift
//  SwiftSample
//
//  Created by roy on 8/3/16.
//  Copyright © 2016 confirm.io. All rights reserved.
//

import UIKit
// import confirm_sdk

class ViewController: UIViewController, ConfirmCaptureDelegate {
	
	@IBOutlet weak var checkIDButton: UIButton!
	@IBOutlet weak var checkIDSelfieButton: UIButton!
	@IBOutlet weak var statusLabel: UILabel!
	@IBOutlet weak var progressLabel: UILabel!
	
	var payload: ConfirmPayload!
	var lastProgress: TimeInterval = 0
	
	
	override func viewDidLoad() 
	{
		super.viewDidLoad()
	}
	
	@IBAction func didTapCheckID(_ sender: UIButton)
	{
		var cc: ConfirmCapture
		var nav: UINavigationController
		
		cc = ConfirmCapture.singleton()
		nav = cc.confirmController()
		
		cc.delegate = self
		cc.enableFacialMatch = false
		
		self.present(nav, animated: true, completion: nil)
		
		self.checkIDButton.isEnabled = false
		self.checkIDSelfieButton.isEnabled = false
		self.setStatusString("")
		self.setProgressString("")
	}
	
	@IBAction func didTapCheckIDSelfie(_ sender: UIButton)
	{
		var cc: ConfirmCapture
		var nav: UINavigationController
		
		cc = ConfirmCapture.singleton()
		nav = cc.confirmController()
		
		cc.delegate = self
		cc.enableFacialMatch = true
		self.present(nav, animated: true, completion: nil)
		
		self.checkIDButton.isEnabled = false
		self.checkIDSelfieButton.isEnabled = false
		self.setStatusString("")
		self.setProgressString("")
	}
	
	func setProgressString(_ value: NSString)
	{
		OperationQueue.main.addOperation { 
			self.progressLabel.text = value as String
		}
	}
	
	func setStatusString(_ value: NSString)
	{
		OperationQueue.main.addOperation { 
			self.statusLabel.text = value as String
		}
	}
	
	
	func confirmCaptureDidComplete(_ payload: ConfirmPayload)
	{
		ConfirmSubmit.singleton().submitIDCapture(payload,
		                                                 onSubmission: nil,
		                                                 onStatus: { (info: Dictionary, state: ConfirmSubmitState) in
															let blurb_: AnyObject? = info[kStatusInfoTitleKey] as! NSString
															var blurb: NSString = "";
															
															if blurb_ != nil {
																blurb = blurb_ as! NSString
																let message_: AnyObject? = info[kStatusInfoMessageKey] as! NSString
																
																if message_ != nil {
																	let message: NSString = message_ as! NSString
																	blurb = blurb.appendingFormat("\n%@", message)
																}
															}
															let guid_ : AnyObject? = info[kStatusInfoGuidKey] as! NSString;
															
															if guid_ != nil {
																let guid: NSString = guid_ as! NSString;
																blurb = NSString.localizedStringWithFormat("\nguid received:\n%@", guid)
															}
															self.setStatusString(blurb);
														},
		                                                 onProgress:{ (progress: Progress, progressType: ConfirmSubmitProgressType) in
															let rightNow: TimeInterval = CACurrentMediaTime()
															
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
															self.checkIDButton.isEnabled = true;
															self.checkIDSelfieButton.isEnabled = true;
														}, 
		                                                 onError:{ (error, guid) in
															NSLog("submission error\n%@", error.localizedDescription)
															ConfirmCapture.singleton().cleanup()
															self.payload = nil
															self.checkIDButton.isEnabled = true;
															self.checkIDSelfieButton.isEnabled = true;
														}
		)
		
		self.finishIDCapture()
	}
	
	func confirmCaptureDidCancel()
	{
		self.finishIDCapture()
	}
	
	func finishIDCapture()
	{
		self.dismiss(animated: true, completion:nil)
	}
	
	func showResults(_ validatedID: IDModel?, facialResponse: FacialMatchResponse?)
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
			
			status = status.appendingFormat(" (%@ %@ %@)\n%@ %@", classification.state, classification.type, issuance.number,
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
			self.setProgressString(progress as NSString)
		}
	}
	
	func memoryString(_ value: Int64) -> NSString?
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

