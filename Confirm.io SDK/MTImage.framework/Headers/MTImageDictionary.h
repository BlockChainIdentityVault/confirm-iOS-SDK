//
//  MTImageDictionary.h
//  MTImage
//
//  Created by clayton on 6/23/15.
//  Copyright (c) 2015 MorphoTrust. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@interface MTImageDictionary : NSObject

//saves the CGImageRef as a PNG file to the App document folder for given file name
+(BOOL)saveImageAsPNG:(CGImageRef)imageRef fileName:(NSString *)name;

//loads image file from the App document folder with given file name
+(UIImage *)loadImageWithFileName:(NSString *)name;

//deletes files from the App document folder  Example usage
//  [MTImagingHelper deleteImageFromNSDocumentDictorywithFileName:@"*" extension:"png"] - deletes all files with extension png
//  [MTImagingHelper deleteImageFromNSDocumentDictorywithFileName:@"*" extension:"*"] - deletes all files
//  [MTImagingHelper deleteImageFromNSDocumentDictorywithFileName:@"file1" extension:"png"] - deletes the file file1.png
+(void)deleteImageWithFileName:(NSString *)fileName fileExtension:(NSString *)extension;

@end
