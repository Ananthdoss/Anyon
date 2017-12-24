#include "AppDelegate.h"
#include "../Core.hpp"
#include "../../Game.hpp"

int main(int argc, char **argv)
{
    [NSApplication sharedApplication];
    
    Core::EventReceiver *appMainReceiver = new Game();
    
    AppDelegate *appDelegate = [[AppDelegate alloc] initWithPlatformWrapper:(PlatformWrapper*)Core::Start(appMainReceiver)];
    
    [NSApp setDelegate:appDelegate];
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
    
    [appDelegate release];
    
    delete appMainReceiver;
    
    return 0;
}
