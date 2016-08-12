//
//  ResultsController.m
//  Sample
//
//  Created by roy on 2/1/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import "ResultsController.h"
#import <confirm_sdk/confirm_sdk.h>

@interface ResultsController ()
@property (nonatomic, strong)	NSArray*	tableArray;
@end

@implementation ResultsController
@synthesize result, facial, tableArray;

+ (ResultsController*)controller
{
	ResultsController* vc = [[ResultsController alloc] initWithNibName:@"ResultsController" bundle:nil];
	vc.edgesForExtendedLayout = UIRectEdgeLeft | UIRectEdgeRight | UIRectEdgeBottom;
	return vc;
}

- (NSString*)facialString
{
	NSString *str = @"";
	
	switch (facial.facialMatchValue) {
		case FacialMatchValueUnknown:
			str = @"Unknown";
			break;
		case FacialMatchValueFailed:
			str = @"Failed";
			break;
		case FacialMatchValuePassed:
			str = @"Passed";
			break;
		case FacialMatchValueError:
			str = @"Error";
			break;
	}
	return str;
}

- (void)viewDidLoad
{
	[super viewDidLoad];
	
	IdentityClassificationModel*	classification = result.identity.classification;
	IdentityIssuanceModel*			issuance = result.identity.issuance;
	IdentityBioModel*				bio = result.identity.bio;
	
	NSDateFormatter*				df = [NSDateFormatter new];
	
	df.dateStyle = kCFDateFormatterShortStyle;
	df.timeStyle = kCFDateFormatterNoStyle;
	df.timeZone = NSTimeZone.systemTimeZone;
	
	self.tableArray = @[
						@{ kResultsDataKey: self.facialString, kResultsTitleKey: @"Facial Match"},
						@{ kResultsDataKey: classification.type, kResultsTitleKey: @"ID Type"},
						@{ kResultsDataKey: classification.state, kResultsTitleKey: @"State" },
						@{ kResultsDataKey: [df stringFromDate: issuance.issued], kResultsTitleKey: @"Issue Date"},
						@{ kResultsDataKey: [df stringFromDate: issuance.expiration], kResultsTitleKey: @"Exp Date"},
						@{ kResultsDataKey: issuance.number, kResultsTitleKey: @"Number"},
						@{ kResultsDataKey: bio.firstName, kResultsTitleKey: @"First Name"},
						@{ kResultsDataKey: bio.middleName, kResultsTitleKey: @"Middle Name"},
						@{ kResultsDataKey: bio.lastName, kResultsTitleKey: @"Last Name"},
						@{ kResultsDataKey: bio.address, kResultsTitleKey: @"Address"},
						@{ kResultsDataKey: bio.city, kResultsTitleKey: @"City"},
						@{ kResultsDataKey: bio.state, kResultsTitleKey: @"State"},
						@{ kResultsDataKey: bio.zip, kResultsTitleKey: @"Zip Code"},
						@{ kResultsDataKey: bio.country, kResultsTitleKey: @"Country"},
						@{ kResultsDataKey: [df stringFromDate:bio.dob], kResultsTitleKey: @"Birthday"},
						@{ kResultsDataKey: bio.gender, kResultsTitleKey: @"Gender"},
						@{ kResultsDataKey: bio.height, kResultsTitleKey: @"Height"},
						@{ kResultsDataKey: bio.weight, kResultsTitleKey: @"Weight"},
					];
	self.navigationController.navigationBarHidden = NO;
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
}

#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	return tableArray.count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"reuseIdentifier"];
    
	if (cell == nil)
		cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleValue2 reuseIdentifier:@"reuseIdentifier"];
	
	NSDictionary* info = tableArray[indexPath.row];
	
	cell.textLabel.text = info[kResultsTitleKey];
	cell.detailTextLabel.text = info[kResultsDataKey];
    return cell;
}

@end
