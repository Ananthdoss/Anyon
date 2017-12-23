#import "AppDelegate.h"

@implementation AppDelegate

- (id) initWithPlatformWrapper:(/*Anyon::PlatformWrapper*/void *)wrapper
{
    if (self = [super init])
    {
        mainMenuBar = [[NSMenu alloc] init];
        appMenuItem = [[NSMenuItem alloc] init];
        [mainMenuBar addItem:appMenuItem];
        [NSApp setMainMenu:mainMenuBar];
        appMenu = [[NSMenu alloc] init];
        appQuitItem = [[NSMenuItem alloc] initWithTitle:[@"Quit " stringByAppendingString:[[NSProcessInfo processInfo] processName]] action:@selector(closeWindow) keyEquivalent:@"q"];
        [appMenu addItem:appQuitItem];
        [appMenuItem setSubmenu:appMenu];
        
        core = [[CoreInterlayer alloc] initWithAppDelegate:self platformWrapper:wrapper];
    }
    
    return self;
}

- (void) dealloc
{
    [core release];
    
    [mainMenuBar release];
    [appMenuItem release];
    [appMenu release];
    [appQuitItem release];
    
    [super dealloc];
}

- (NSRect) calculateWindowRect
{
    const NSRect dispRect = [[NSScreen mainScreen] frame];
    
    if (core.configFullscreen)
    {
        if (core.configWidth == -1)
            core.configWidth = dispRect.size.width;
        
        if (core.configHeight == -1)
            core.configHeight = dispRect.size.height;
        
        return NSMakeRect(0, 0, dispRect.size.width, dispRect.size.height);
    }
    else
    {
        if (core.configWidth == -1)
            core.configWidth = dispRect.size.width / 2;
        
        if (core.configHeight == -1)
            core.configHeight = dispRect.size.height / 2;
        
        return NSMakeRect((dispRect.size.width - core.configWidth) / 2, (dispRect.size.height - core.configHeight) / 2, core.configWidth, core.configHeight);
    }
}

- (void) createWindow
{
    window = [[NSWindow alloc] initWithContentRect:[self calculateWindowRect]
                                         styleMask:core.configFullscreen ? NSWindowStyleMaskBorderless : NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
                                           backing:NSBackingStoreBuffered
                                             defer:YES];
    
    window.title = [[NSProcessInfo processInfo] processName];
    
    [window setOpaque:YES];
    [window setHidesOnDeactivate:core.configFullscreen ? YES : NO];
    [window setReleasedWhenClosed:NO];
    [window setAcceptsMouseMovedEvents:YES];
    
    if (core.configFullscreen)
        [window setLevel:NSMainMenuWindowLevel + 1];
    
    doReconfigureOnWindowClose = NO;
}

- (void) reconfigureWindow
{
    doReconfigureOnWindowClose = YES;
    [view initiateReconfig];
}

- (void) applicationWillFinishLaunching:(NSNotification *)aNotification
{
    [self createWindow];
    
    view = [[OpenGLView alloc] initWithFrame:window.frame coreInterlayer:core];
    view.ownerWindow = window;
    
    [window setContentView:view];
    [window makeFirstResponder:view];
    
    [view reshape];
    view.needsDisplay = YES;
}

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification object:window];
    
    [core initialize];
    
    [view activate];
    [window makeKeyAndOrderFront:self];
}

- (void) closeWindow
{
    [window close];
}

- (void) windowWillClose:(NSNotification *)notification
{
    [[NSNotificationCenter defaultCenter] removeObserver:self name:NSWindowWillCloseNotification object:window];
    [view deactivate];
    [window release];
    
    if (doReconfigureOnWindowClose)
    {
        [self createWindow];
        
        view.ownerWindow = window;
        [window setContentView:view];
        [window makeFirstResponder:view];
        
        [view reconfig];
        [view reshape];
        view.needsDisplay = YES;
        
        [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification object:window];
        
        [view activate];
        
        [window makeKeyAndOrderFront:self];
    }
    else
    {
        [core finalize];
        [view release];
        [NSApp stop:self];
    }
}

@end
