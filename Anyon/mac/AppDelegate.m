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
        
        engine = [[EngineInterlayer alloc] initWithAppDelegate:self platformWrapper:wrapper];
    }
    
    return self;
}

- (void) dealloc
{
    [engine release];
    
    [mainMenuBar release];
    [appMenuItem release];
    [appMenu release];
    [appQuitItem release];
    
    [super dealloc];
}

- (NSRect) calculateWindowRect
{
    const NSRect dispRect = [[NSScreen mainScreen] frame];
    
    if (engine.configFullscreen)
    {
        if (engine.configWidth == -1)
            engine.configWidth = dispRect.size.width;
        
        if (engine.configHeight == -1)
            engine.configHeight = dispRect.size.height;
        
        return NSMakeRect(0, 0, dispRect.size.width, dispRect.size.height);
    }
    else
    {
        if (engine.configWidth == -1)
            engine.configWidth = dispRect.size.width / 2;
        
        if (engine.configHeight == -1)
            engine.configHeight = dispRect.size.height / 2;
        
        return NSMakeRect((dispRect.size.width - engine.configWidth) / 2, (dispRect.size.height - engine.configHeight) / 2, engine.configWidth, engine.configHeight);
    }
}

- (void) createWindow
{
    window = [[NSWindow alloc] initWithContentRect:[self calculateWindowRect]
                                         styleMask:engine.configFullscreen ? NSWindowStyleMaskBorderless : NSWindowStyleMaskTitled | NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable
                                           backing:NSBackingStoreBuffered
                                             defer:YES];
    
    window.title = [[NSProcessInfo processInfo] processName];
    
    [window setOpaque:YES];
    [window setHidesOnDeactivate:engine.configFullscreen ? YES : NO];
    [window setReleasedWhenClosed:NO];
    [window setAcceptsMouseMovedEvents:YES];
    
    if (engine.configFullscreen)
        [window setLevel:NSMainMenuWindowLevel + 1];
    
    doReconfigureOnWindowClose = NO;
}

- (void) reconfigureWindow
{
    doReconfigureOnWindowClose = YES;
    [window close];
}

- (void) applicationWillFinishLaunching:(NSNotification *)aNotification
{
    [self createWindow];
    
    view = [[OpenGLView alloc] initWithFrame:window.frame engineInterlayer:engine];
    view.ownerWindow = window;
    
    [window setContentView:view];
    [window makeFirstResponder:view];
    
    [view reshape];
    view.needsDisplay = YES;
}

- (void) applicationDidFinishLaunching:(NSNotification *)aNotification
{
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(windowWillClose:) name:NSWindowWillCloseNotification object:window];
    
    [engine initialize];
    
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
        [engine finalize];
        [view release];
        [NSApp stop:self];
    }
}

@end
