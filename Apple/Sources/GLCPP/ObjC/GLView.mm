#import <math.h>
#import <GLCPP/ObjC/GLView.h>

@implementation GLView

- (BOOL)isAnimating { return YES; }
- (void)startAnimation {}
- (void)stopAnimation {}

//
// Overriden methods
//

- (void)awakeFromNib
{
    displayLink = 0;
    cglContext = 0;
    needToSetCGLContextInDisplayLink = true;

    auto pixelFormat = [self selectPixelFormat];
    NSOpenGLContext* context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    cglContext = (CGLContextObj)[context CGLContextObj];
    CGLEnable((CGLContextObj)[context CGLContextObj], kCGLCECrashOnRemovedFunctions);

    [self setPixelFormat:pixelFormat];
    [self setOpenGLContext:context];
}

- (BOOL)acceptsFirstResponder {
  return YES;
}

- (BOOL)becomeFirstResponder {
  return YES;
}

- (BOOL)resignFirstResponder {
  return YES;
}

- (BOOL)mouseDownCanMoveWindow {
    return NO;
}

- (void)prepareOpenGL
{
    [[self openGLContext] makeCurrentContext];

    GL::printInfo();
    [self setGLOptions];
    [self onGlReady];

    [self prepareDisplayLink];
}

- (void)clearGLContext {}

- (void)windowWillClose:(NSNotification*)notification {
    if (displayLink) {
        CVDisplayLinkStop(displayLink);
        CVDisplayLinkRelease(displayLink);
        displayLink = 0;
    }

    printf("allocs: %llu,  deallocs: %llu\n", Rt::Object::allocsCount, Rt::Object::deallocsCount);
}

static CVReturn displayLinkCallback(CVDisplayLinkRef displayLink,
                                    const CVTimeStamp* now,
                                    const CVTimeStamp* outputTime,
                                    CVOptionFlags flagsIn,
                                    CVOptionFlags* flagsOut,
                                    void* context)
{
    return [(__bridge GLView*)context getFrameForTime:outputTime];
}

- (CVReturn)getFrameForTime:(const CVTimeStamp*)outputTime {
    //static uint64_t lastTime = 0;
    static float angle = 0.0f;

    if (needToSetCGLContextInDisplayLink) {
        CGLSetCurrentContext(cglContext);
        needToSetCGLContextInDisplayLink = false;
    }

//    auto dt = (lastTime != 0 ? outputTime->videoTime - lastTime : 0);
    [self prepareScene:outputTime->videoTime];

#if 0
    NSLog(@"%u %d %lld %llu %lf %lld %llu",
          outputTime->version,		      // Currently will be 0.
          outputTime->videoTimeScale,     // Video timescale (units per second)
          outputTime->videoTime,		  // This represents the start of a frame (or field for interlaced) .. think vsync  - still not 100% sure on the name
          outputTime->hostTime,		      // Host root timebase time
          outputTime->rateScalar,		  // Current rate as measured by the timestamps divided by the nominal rate
          outputTime->videoRefreshPeriod, // Hint for nominal output rate
          outputTime->flags
    );
#endif

//    printf("%f\n", 1.0 / (double(outputTime->videoTime - lastTime) / double(outputTime->videoTimeScale)));
    //lastTime = outputTime->videoTime;

#if 0
    float fps = 1.0f / ((1.0f / outputTime->videoTimeScale) * outputTime->videoRefreshPeriod);
    printf("FPS: %f\n", fps);
//    printf("%f\n", double(outputTime->videoTime) / double(outputTime->videoTimeScale));
#endif

    return kCVReturnSuccess;
}

- (void)drawRect:(NSRect)rect
{
    CGLLockContext(cglContext);
    [self drawScene];
    CGLFlushDrawable(cglContext);
    CGLUnlockContext(cglContext);
}

- (void)printGLInfo {
    printf("Vendor: %s\n", glGetString(GL_VENDOR));
    printf("Renderer: %s\n", glGetString(GL_RENDERER));
    printf("Version: %s\n", glGetString(GL_VERSION));
    printf("Extensions:\n");

    GLint extensionsCount;
    glGetIntegerv(GL_NUM_EXTENSIONS, &extensionsCount);
    for (auto i = 0; i < extensionsCount; i++)
        printf("  %s\n", glGetStringi(GL_EXTENSIONS, i));

    GLint maxGeometryOutputVertices;
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &maxGeometryOutputVertices);
    printf("Max geometry output vertices: %u\n", maxGeometryOutputVertices);
/*
    GLint maxGeometryOutputVertices;
    glGetIntegerv(GL_MAX_GEOMETRY_OUTPUT_VERTICES, &maxGeometryOutputVertices);
    printf("Max geometry output vertices: %u\n", maxGeometryOutputVertices);
*/
}

// kCGLCPSurfaceOpacity
- (void)prepareDisplayLink
{
    GLint swapInterval = 1;
    [[self openGLContext] setValues:&swapInterval forParameter:NSOpenGLCPSwapInterval]; 

    GLint opaque = 1;
    [[self openGLContext] setValues:&opaque forParameter:NSOpenGLCPSurfaceOpacity];

    if (CVDisplayLinkCreateWithActiveCGDisplays(&displayLink) != kCVReturnSuccess)
        Rt::error(0x2E32B05C);

    if (CVDisplayLinkSetOutputCallback(displayLink, &displayLinkCallback, (__bridge void*)self) != kCVReturnSuccess)
        Rt::error(0xCBE0816E);

    auto cglPixelFormat = CGLPixelFormatObj([[self pixelFormat] CGLPixelFormatObj]);
    if (!cglPixelFormat) Rt::error(0x62D5BA5D);

    if (CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, cglContext, cglPixelFormat) != kCVReturnSuccess)
        Rt::error(0x52690D3A);

    if (CVDisplayLinkStart(displayLink) != kCVReturnSuccess)
        Rt::error(0xA26E126A);

	[[NSNotificationCenter defaultCenter] addObserver:self
											 selector:@selector(windowWillClose:)
												 name:NSWindowWillCloseNotification
											   object:[self window]];
}

//
// Events
//

- (void) update
{
    [super update];

    GLint newVirtualScreen = [[self openGLContext] currentVirtualScreen];
    if (virtualScreen != newVirtualScreen) {
        virtualScreen = newVirtualScreen;
        // Adapt to any changes in capabilities
        // (such as max texture size and hardware capabilities).
    }
}

- (void)reshape
{
    [super reshape];
    CGLLockContext(cglContext);
    [self reshape:[self frame].size];
    CGLUnlockContext(cglContext);
}

- (void)renewGState
{	
	// Called whenever graphics state updated (such as window resize)
	
	// OpenGL rendering is not synchronous with other rendering on the OSX.
	// Therefore, call disableScreenUpdatesUntilFlush so the window server
	// doesn't render non-OpenGL content in the window asynchronously from
	// OpenGL content, which could cause flickering.  (non-OpenGL content
	// includes the title bar and drawing done by the app with other APIs)
	[[self window] disableScreenUpdatesUntilFlush];
	[super renewGState];
}

- (void)mouseDragged:(NSEvent*)event
{
    auto p = [self convertPoint:[event locationInWindow] fromView:0];
    auto dx = [event deltaX];
    auto dy = [event deltaY];
    [self move:p.x y:p.y dx:dx dy:dy event:event];
    [super mouseDragged:event];
}

- (void)touchpadScroll:(NSEvent*)event {
    auto p = [self convertPoint:[event locationInWindow] fromView:0];
    auto dx = [event deltaX];
    auto dy = [event deltaY];
    [self move:p.x y:p.y dx:dx dy:dy event:event];
}

- (void)mouseScroll:(NSEvent*)event
{
    auto p = [self convertPoint:[event locationInWindow] fromView:0];
    auto dx = [event scrollingDeltaX];
    auto dy = [event scrollingDeltaY];
    [self scroll:p.x y:p.y dx:dx dy:dy event:event];
}

- (void)scrollWheel:(NSEvent*)event
{
    switch ([event subtype])
    {
        case NSMouseEventSubtype:
            [self mouseScroll:event];
        break;

        case NSTabletPointEventSubtype:
            [self touchpadScroll:event];
        break;

        default: break;
    }
}

//
// Override in subclasses
//

- (void)reshape:(NSSize)size
{}

- (void)scroll:(float)x y:(float)y dx:(float)dx dy:(float)dy event:(NSEvent*)event {}

- (void)move:(float)x y:(float)y dx:(float)dx dy:(float)dy event:(NSEvent*)event {}

- (void)setGLOptions
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);

#if defined __APPLE__ && TARGET_OS_IPHONE
    glDepthRangef(0.0, 1.0);
#else
//    glDepthRange(0.5, 100.0);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
#endif

    glDepthRange(0.0f, 1.0f);

#if 1
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#endif

#if 0
    #ifndef GL_POINT_SMOOTH
        #define GL_POINT_SMOOTH 0x0B10
    #endif

    //glEnable(GL_POINT_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
#endif

    glFrontFace(GL_CCW);

#if 0
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, -1.0);
#endif

//    glClearColor(backgroundColor[0], backgroundColor[1], backgroundColor[2], 0.0);
//    glLineWidth(2.0);

    float c = 0.0f;
    glClearColor(c, c, c, 1.0f);
}

- (void)onGlReady {}

- (void)prepareScene:(Rt::u8)dt {
}

- (void)drawScene {
}

- (NSOpenGLPixelFormat*)selectPixelFormat
{
    NSOpenGLPixelFormatAttribute attributes[][16] =
    {
// No-recovery:
  // 32-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            NSOpenGLPFANoRecovery,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            NSOpenGLPFANoRecovery,
            0
        },
  // 24-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFANoRecovery,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFANoRecovery,
            0
        },
  // 24-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            NSOpenGLPFANoRecovery,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            NSOpenGLPFANoRecovery,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            NSOpenGLPFANoRecovery,
            0
        },
// Recoverable mode (possibly software renderer :( )
  // 32-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
  // 24-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
  // 24-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFAAccelerated,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
// Non-accelerated:
  // 32-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 32,
            0
        },
  // 24-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 24,
            0
        },
  // 24-bit depth:
    // Multisample 16:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 16,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Multisample 8:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 8,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Multisample 4:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 4,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Multisample 2:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAMultisample,
            NSOpenGLPFASampleAlpha,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, 2,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    // Non-multisampled:
        {
            NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
            NSOpenGLPFADoubleBuffer,
            NSOpenGLPFAColorSize, 32,
            NSOpenGLPFADepthSize, 16,
            0
        },
    };

    for (int i = 0; i < sizeof(attributes) / sizeof(attributes[0]); i++)
    {
        auto result = [[NSOpenGLPixelFormat alloc] initWithAttributes:attributes[i]];
        if (result)
        {
            printf("Selected pixel format %u: ", i);
            for (int j = 0; j < sizeof(attributes[0]) / sizeof(NSOpenGLPixelFormatAttribute); j++)
                printf("%u ", attributes[i][j]);
            printf("\n");
            return result;
        }
    }

    return nullptr;
}

@end
