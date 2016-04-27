//
//  ResultsController.h
//  Sample
//
//  Created by roy on 2/1/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import <UIKit/UIKit.h>

#define kResultsDataKey		@"data"
#define kResultsTitleKey	@"title"

@class IDModel;
@class FacialMatchResponse;

@interface ResultsController : UITableViewController

@property (nonatomic, strong)	IDModel*				result;
@property (nonatomic, strong)	FacialMatchResponse*	facial;

+ (ResultsController*)controller;

@end
