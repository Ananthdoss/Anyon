#import <Cocoa/Cocoa.h>
#import "EngineInterlayer.h"

@interface OpenGLView : NSView
{
@private
    NSOpenGLContext *context;
    NSOpenGLPixelFormat *pixelFormat;
    CVDisplayLinkRef displayLink;
    NSWindow *window;
    EngineInterlayer *engine;
}

@property (assign) NSWindow *ownerWindow;

- (id) initWithFrame:(NSRect)frameRect engineInterlayer:(EngineInterlayer *)engine;
- (void) reconfig;
- (void) reshape;
- (void) activate;
- (void) deactivate;

@end
