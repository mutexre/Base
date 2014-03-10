#import <Cocoa/Cocoa.h>
#import <CoreVideo/CVDisplayLink.h>
#import <Runtime/Runtime.h>
#import <Math/Math.h>
#import <GLCPP/GL.h>

@interface GLView : NSOpenGLView
{
@protected
    CGLContextObj cglContext;
    CVDisplayLinkRef displayLink;
    GLint virtualScreen;
    bool needToSetCGLContextInDisplayLink;
}

// Overriden methods
- (void)awakeFromNib;
- (BOOL)acceptsFirstResponder;
- (BOOL)becomeFirstResponder;
- (BOOL)resignFirstResponder;
- (BOOL)mouseDownCanMoveWindow;
- (void)prepareOpenGL;
- (void)clearGLContext;
- (void)windowWillClose:(NSNotification*)notification;
- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime;
- (void)drawRect:(NSRect)rect;

// Subroutines
- (void)printGLInfo;
- (void)prepareDisplayLink;

// Events
- (void)update;
- (void)reshape;
- (void)renewGState;
- (void)keyDown:(NSEvent*)event;
- (void)keyUp:(NSEvent*)event;
- (void)mouseUp:(NSEvent*)event;
- (void)mouseDragged:(NSEvent*)event;
- (void)touchpadScroll:(NSEvent*)event;
- (void)mouseScroll:(NSEvent*)event;
- (void)scrollWheel:(NSEvent*)event;

// Override in subclasses
- (NSOpenGLPixelFormat*)selectPixelFormat;
- (void)setGLOptions;
- (void)onGlReady;
- (void)prepareScene;
- (void)drawScene;
- (void)reshape:(NSSize)size;
- (void)scroll:(float)x y:(float)y dx:(float)dx dy:(float)dy event:(NSEvent*)event;
- (void)move:(float)x y:(float)y dx:(float)dx dy:(float)dy event:(NSEvent*)event;

@end
