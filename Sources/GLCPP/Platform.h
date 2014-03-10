#ifndef header_14DA4854F91E
#define header_14DA4854F91E

#ifdef __APPLE__

    #include "TargetConditionals.h"

    #if TARGET_OS_IPHONE
        #import <OpenGLES/ES2/gl.h>
        #import <OpenGLES/ES2/glext.h>
    #elif TARGET_OS_MAC
        #include <OpenGL/gl3.h>
        #include <OpenGL/gl3ext.h>
    #endif

#elif defined(__linux)
    #error not implemented
#elif defined _WIN32 || defined _WIN64
    #include <windows.h>
    #include <GL/glew.h>
    #include <GL/wglew.h>
    //#include <GL/GL.h>
#endif

#endif
