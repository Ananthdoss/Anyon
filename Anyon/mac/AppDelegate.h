#import <Cocoa/Cocoa.h>
#import "EngineInterlayer.h"
#import "OpenGLView.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
@private
    EngineInterlayer *engine;
    NSMenu *mainMenuBar;
    NSMenuItem *appMenuItem;
    NSMenu *appMenu;
    NSMenuItem *appQuitItem;
    
    NSWindow *window;
    OpenGLView *view;
    
    BOOL doReconfigureOnWindowClose;
}
- (id) initWithPlatformWrapper:(/*Anyon::PlatformWrapper*/void *)wrapper;
- (void) reconfigureWindow;

@end
