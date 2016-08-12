//
//  AppDelegate.m
//  Sample
//
//  Created by roy on 2/1/16.
//  Copyright © 2016 Confirm.io. All rights reserved.
//

#import "AppDelegate.h"
#import "ViewController.h"
#import <confirm_sdk/confirm_sdk.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions
{
	UIWindow*				appwindow = [[UIWindow alloc] initWithFrame:UIScreen.mainScreen.bounds];
	UIViewController*		viewController = ViewController.controller;
	UINavigationController* navController = [[UINavigationController alloc] initWithRootViewController:viewController];
	
	self.window = appwindow;
	self.window.rootViewController = navController;
	[appwindow makeKeyAndVisible];

	#warning need to get API Key from confirm.io
	ConfirmSubmit.singleton.apiKey = @"{API KEY}";
	
	#warning need to get MorphoTrust API Key from confirm.io
	[ConfirmSubmit.singleton setMorphoTrustAPIKey:@"{MorphoTrust API KEY}"
										   andURL:@"{MorphoTrust URL}"];

	[ConfirmAppSupport didFinishLaunching];
	return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application
{
}

- (void)applicationDidEnterBackground:(UIApplication *)application
{
}

- (void)applicationWillEnterForeground:(UIApplication *)application
{
}

- (void)applicationDidBecomeActive:(UIApplication *)application
{
}

- (void)applicationWillTerminate:(UIApplication *)application
{
}

@end
