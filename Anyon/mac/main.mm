#include "AppDelegate.h"
#include "../Core.hpp"
#include "../../Game.hpp"

int main(int argc, char **argv)
{
    [NSApplication sharedApplication];
    
    Core::Application *app = new Game();
    
    AppDelegate *appDelegate = [[AppDelegate alloc] initWithPlatformWrapper:(PlatformWrapper*)Core::Start(app)];
    
    [NSApp setDelegate:appDelegate];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
    
    [appDelegate release];
    
    delete app;
    
    return 0;
}
