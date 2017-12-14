#include "AppDelegate.h"
#include "../Engine.hpp"
#include "../../Game.hpp"

int NSLogPrintf(const char * __restrict format, ...)
{
    va_list args;
    va_start(args,format);
    NSLogv([NSString stringWithUTF8String:format], args);
    va_end(args);
    return 1;
}

int main(int argc, char **argv)
{
    [NSApplication sharedApplication];
    
    Engine::Application *app = new Game();
    AppDelegate *appDelegate = [[AppDelegate alloc] initWithPlatformWrapper:(PlatformWrapper*)Engine::Instance()];
    [NSApp setDelegate:appDelegate];
    Engine::Instance()->Start(app);
    
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp run];
    
    [appDelegate release];
    
    delete app;
    
    return 0;
}

