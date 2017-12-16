#import <Cocoa/Cocoa.h>
#import "CoreInterlayer.h"
#import "OpenGLView.h"

@interface AppDelegate : NSObject <NSApplicationDelegate>
{
@private
    CoreInterlayer *core;
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
