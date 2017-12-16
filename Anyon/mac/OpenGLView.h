#import <Cocoa/Cocoa.h>
#import "CoreInterlayer.h"

@interface OpenGLView : NSView
{
@private
    NSOpenGLContext *context;
    NSOpenGLPixelFormat *pixelFormat;
    CVDisplayLinkRef displayLink;
    NSWindow *window;
    CoreInterlayer *core;
}

@property (assign) NSWindow *ownerWindow;

- (id) initWithFrame:(NSRect)frameRect coreInterlayer:(CoreInterlayer *)core;
- (void) reconfig;
- (void) reshape;
- (void) activate;
- (void) deactivate;

@end
