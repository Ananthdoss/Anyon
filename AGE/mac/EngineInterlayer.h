#import <Cocoa/Cocoa.h>

@class AppDelegate;

@interface EngineInterlayer : NSObject
{
    AppDelegate *appDelegate;
    NSUInteger keyMask;
    NSCharacterSet *alphanumeric, *punctuation, *symbol;
    /*AGE::PlatformWrapper*/void *wrapper;
}

- (id) initWithAppDelegate:(AppDelegate *)delegate platformWrapper:(/*AGE::PlatformWrapper*/void *)wrapper;

@property (assign) unsigned configWidth;
@property (assign) unsigned configHeight;
@property (readonly) bool configFullscreen;
@property (readonly) bool configVsync;
@property (assign) bool configFsaa;

- (void) initialize;
- (void) free;
- (bool) mainLoop;
- (void) resize:(NSRect)rect;
- (void) gotFocus;
- (void) lostFocus;
- (void) setKey:(unsigned short)key status:(bool)down;
- (void) setKeyFlags:(NSUInteger)mask;
- (void) inputCharacter:(unichar)c;
- (void) setLeftMouseButton:(bool)pressed;
- (void) setRightMouseButton:(bool)pressed;
- (void) setMouseWheel:(int)pos;
- (void) setMousePosition:(NSPoint)pos;
- (void) fatalAlert:(NSString *)message;
- (void) toggleCursorVisiblity:(bool)visible;
- (void) reconfigureWindow;

#include "EngineInterlayer-CPP-Interface.h"

@end
