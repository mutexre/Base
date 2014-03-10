#import <Runtime/Runtime.h>
#import <GLCPP/ObjC/Subroutines.h>

std::string stringFromTextResource(NSString* name, NSString* extension)
{
    NSString* resourcePath = [[NSBundle mainBundle] pathForResource:name ofType:extension];
    if (resourcePath) return Rt::readFile([resourcePath UTF8String]);
    Rt::error(0x0FF9A5CC);
}

NSBitmapImageRep* getBitmapImageRep(NSString* name, NSString* ext)
{
    auto path = [[NSBundle mainBundle] pathForResource:name ofType:ext];
    if (path)
    {
        NSData* data = [NSData dataWithContentsOfFile:path];
        if (!data) return nil;

        return [NSBitmapImageRep imageRepWithData:data];
/*
            auto tmpData = malloc(128 * 128 * 4);
            if (!tmpData) return false;

            for (int i = 0; i < 128; i++)
            {
                for (int j = 0; j < 128; j++)
                {
                    ((int*)tmpData)[i * 128 + j] = 0xff3f0f00 + 4 * (i ^ j);
                }
            }

            *data = tmpData;
*/
    }

    return nil;
}
