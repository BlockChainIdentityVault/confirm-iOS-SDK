//
//  InterstitialVC.m
//  Sample
//
//  Created by roy on 5/11/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import "InterstitialVC.h"

@interface InterstitialVC ()

@property (weak, nonatomic) IBOutlet UILabel *textLabel;
@property (weak, nonatomic) IBOutlet UIButton *previousButton;
@property (weak, nonatomic) IBOutlet UIButton *nextButton;

@property (copy, nonatomic) void (^completion)(BOOL next);
@property (copy, nonatomic) NSString* message;

@end

@implementation InterstitialVC

+ (InterstitialVC*)controller:(NSString*)message completion:(void(^)(BOOL next))completion
{
	InterstitialVC* vc = [[InterstitialVC alloc] initWithNibName:@"InterstitialVC" bundle:nil];
	
	vc.completion = completion;
	vc.message = message;
	return vc;
}

- (void)viewDidLoad 
{
    [super viewDidLoad];
	
	self.textLabel.text = self.message;
}

- (IBAction)tappedPrevious:(UIButton*)sender
{
	self.previousButton.hidden = YES;
	self.nextButton.hidden = YES;
	if (self.completion)
		self.completion(NO);
}

- (IBAction)tappedNext:(UIButton*)sender
{
	self.previousButton.hidden = YES;
	self.nextButton.hidden = YES;
	if (self.completion)
		self.completion(YES);
}

- (void)viewWillAppear:(BOOL)animated
{
	[super viewWillAppear:animated];
	self.previousButton.hidden = self.navigationController.viewControllers.count == 1;
	self.nextButton.hidden = NO;
}

- (void)dealloc
{
	self.completion = nil;
}

@end
