#import "OpenGLView.h"
#import "AppDelegate.h"

#define MSAA_BUFFERS 4
//#define REQUIRE_ACCELERATION

@implementation OpenGLView

- (NSWindow *) ownerWindow
{
    return window;
}

- (void) setOwnerWindow:(NSWindow *) window
{
    if (self->window)
    {
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NSWindowDidBecomeKeyNotification object:self->window];
        [[NSNotificationCenter defaultCenter] removeObserver:self name:NSWindowDidResignKeyNotification object:self->window];
    }
    
    self->window = window;
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didBecomeKeyNotification:) name:NSWindowDidBecomeKeyNotification object:self->window];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didResignKeyNotification:) name:NSWindowDidResignKeyNotification object:self->window];
}

- (CVReturn) getFrameForTime:(const CVTimeStamp *)outputTime
{
    [self drawView];
    
    if (initiateReconfig)
    {
        initiateReconfig = NO;
        [self deactivate];
        dispatch_async(dispatch_get_main_queue(), ^{
            [self releaseDisplayLink];
            [window close];
        });
    }
    
    return kCVReturnSuccess;
}

static CVReturn MyDisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp *now, const CVTimeStamp *outputTime, CVOptionFlags flagsIn, CVOptionFlags *flagsOut, void *displayLinkContext)
{
   return [(OpenGLView*)displayLinkContext getFrameForTime:outputTime];
}

- (void) setupDisplayLink
{
    CVDisplayLinkCreateWithActiveCGDisplays(&displayLink);
    CVDisplayLinkSetOutputCallback(displayLink, &MyDisplayLinkCallback, self);
    CVDisplayLinkSetCurrentCGDisplayFromOpenGLContext(displayLink, [context CGLContextObj], [pixelFormat CGLPixelFormatObj]);
}

- (void) releaseDisplayLink
{
    CVDisplayLinkStop(displayLink);
    CVDisplayLinkRelease(displayLink);
    displayLink = nil;
}

- (id) initWithFrame:(NSRect)frameRect coreInterlayer:(CoreInterlayer *)core
{
    if (self = [super initWithFrame:frameRect])
    {
        initiateReconfig = NO;
        window = nil;
        self->core = core;
        
        const NSOpenGLPixelFormatAttribute attribs_common[] =
        {
#ifdef REQUIRE_ACCELERATION
            NSOpenGLPFAAccelerated,
#endif
            NSOpenGLPFATripleBuffer,
            NSOpenGLPFAColorSize, 24,
            NSOpenGLPFAAlphaSize, 8,
            NSOpenGLPFADepthSize, 24,
            NSOpenGLPFAStencilSize, 8,
            NSOpenGLPFAOpenGLProfile,
            NSOpenGLProfileVersion4_1Core,
            core.configFsaa ? NSOpenGLPFAMultisample : 0,
            NSOpenGLPFASampleBuffers, 1,
            NSOpenGLPFASamples, MSAA_BUFFERS,
            0
        };
        
        pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:attribs_common];
        
        if (!pixelFormat)
            [self->core fatalAlert:@"No suitable OpenGL 4.1 pixel format found!"];
        
        self->context = [[NSOpenGLContext alloc] initWithFormat:pixelFormat shareContext:nil];
    
        [context makeCurrentContext];
        
        const GLint swap = core.configVsync ? 1 : 0;
        [context setValues:&swap forParameter:NSOpenGLCPSwapInterval];
        
        [self setupDisplayLink];
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reshape) name:NSViewGlobalFrameDidChangeNotification object:self];
    }
    
    return self;
}

- (void) lockFocus
{
    [super lockFocus];
    if ([context view] != self)
        [context setView:self];
}

- (void) initiateReconfig
{
    initiateReconfig = YES;
}

- (void) reconfig
{
    [context makeCurrentContext];
    
    const GLint swap = core.configVsync ? 1 : 0;
    [context setValues:&swap forParameter:NSOpenGLCPSwapInterval];
    
    GLint val;
    [pixelFormat getValues:&val forAttribute:NSOpenGLPFASamples forVirtualScreen:0];
    if ((val == MSAA_BUFFERS) != core.configFsaa)
    {
        core.configFsaa = val == MSAA_BUFFERS;
        NSLog(@"Can not change FSAA settings after initialization!");
    }
    
    [self setupDisplayLink];
}

- (void) reshape
{
    CGLLockContext([context CGLContextObj]);
    
    NSRect bounds = [self bounds];
    
    if (bounds.size.width != core.configWidth || bounds.size.height != core.configHeight)
    {
        NSLog(@"Switching to non-native fullscreen resolution currently is not supported!");
        core.configWidth = bounds.size.width;
        core.configHeight = bounds.size.height;
        
        // Issue: For some reason this code doesn't work!
        /*const GLint dim[2] = {core.configWidth, core.configHeight };
        CGLSetParameter([context CGLContextObj], kCGLCPSurfaceBackingSize, dim);
        CGLEnable([context CGLContextObj], kCGLCESurfaceBackingSize);*/
        
        //bounds.size.width = core.configWidth;
        //bounds.size.height = core.configHeight;
        [core resize:bounds];
    }
    else
    {
        CGLDisable([context CGLContextObj], kCGLCESurfaceBackingSize);
        [core resize:bounds];
    }
    
    [context update];
    
    CGLUnlockContext([context CGLContextObj]);

}

- (void) renewGState
{
    [window disableScreenUpdatesUntilFlush];
    [super renewGState];
}

- (void) drawRect:(NSRect)dirtyRect
{
    if (!CVDisplayLinkIsRunning(displayLink))
       [self drawView];
}

- (void) drawView
{
    CGLLockContext([context CGLContextObj]);
    
    [context makeCurrentContext];
    
    if (![core mainLoop])
        dispatch_async(dispatch_get_main_queue(), ^{
            [window close];
        });
    
    [context flushBuffer];
    
    CGLUnlockContext([context CGLContextObj]);
}

- (BOOL) aceptsFirstResponder
{
    return YES;
}

- (void) didBecomeKeyNotification:(NSNotification *)notification
{
    [core gotFocus];
}

- (void) didResignKeyNotification:(NSNotification *)notification
{
    [core lostFocus];
}

- (void) keyDown:(NSEvent *)event
{
    [core setKey:[event keyCode] status:true];
    
    [core inputCharacter:[[event charactersIgnoringModifiers] characterAtIndex:0]];
}

- (void) keyUp:(NSEvent *)event
{
    [core setKey:[event keyCode] status:false];
}

- (void) mouseMoved:(NSEvent *)event
{
    [core setMousePosition:[event locationInWindow]];
}

- (void) mouseDown:(NSEvent *)event
{
    switch ([event type])
    {
        case NSEventTypeLeftMouseDown:
            [core setLeftMouseButton:true];
            break;
        case NSEventTypeRightMouseDown:
            [core setRightMouseButton:true];
            break;
        default:
            break;
    }
}

- (void) mouseUp:(NSEvent *)event
{
    switch ([event type])
    {
        case NSEventTypeLeftMouseUp:
            [core setLeftMouseButton:false];
            break;
        case NSEventTypeRightMouseUp:
            [core setRightMouseButton:false];
            break;
        default:
            break;
    }
}

- (void) scrollWheel:(NSEvent *)event
{
    [core setMouseWheel:[event deltaY]];
}

- (void) flagsChanged:(NSEvent *)event
{
    [core setKeyFlags:[event modifierFlags]];
}

- (void) activate
{
    if(displayLink && !CVDisplayLinkIsRunning(displayLink))
        CVDisplayLinkStart(displayLink);
}

- (void) deactivate
{
    if(displayLink && CVDisplayLinkIsRunning(displayLink))
        CVDisplayLinkStop(displayLink);
}

- (void) dealloc
{
    [self releaseDisplayLink];
    
    [context release];
    [pixelFormat release];
    
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NSWindowDidBecomeKeyNotification object:window];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NSWindowDidResignKeyNotification object:window];
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NSViewGlobalFrameDidChangeNotification object:self];
    
    [super dealloc];
}

@end
