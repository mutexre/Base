#include <string>
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

std::string stringFromTextResource(NSString* name, NSString* extension);
NSBitmapImageRep* getBitmapImageRep(NSString* name, NSString* ext);
