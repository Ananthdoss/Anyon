#import "EngineInterlayer.h"
#import "AppDelegate.h"

#include "../Engine.hpp"

using namespace AGE;

@implementation EngineInterlayer

- (id) initWithAppDelegate:(AppDelegate *)delegate platformWrapper:(void *)wrapper
{
    if (self = [super init])
    {
        appDelegate = delegate;
        self->wrapper = wrapper;
        ((PlatformWrapper *)self->wrapper)->SetInterlayerInstanceId(self);
        keyMask = 0;
        alphanumeric = [NSCharacterSet alphanumericCharacterSet];
        punctuation = [NSCharacterSet punctuationCharacterSet];
        symbol = [NSCharacterSet symbolCharacterSet];
    }
        
    return self;
}

- (unsigned) configWidth;
{
    return Engine::config.width;
}

- (void) setConfigWidth:(unsigned) width
{
    Engine::config.width = width;
}

- (unsigned) configHeight
{
    return Engine::config.height;
}

- (void) setConfigHeight:(unsigned) height
{
    Engine::config.height = height;
}

- (bool) configFullscreen
{
    return Engine::config.fullscreen;
}

- (bool) configVsync
{
    return Engine::config.vsync;
}

- (bool) configFsaa
{
    return Engine::config.fsaa;
}

- (void) setConfigFsaa:(bool) fsaa
{
    Engine::config.fsaa = fsaa;
}

- (void) initialize
{
    ((PlatformWrapper *)wrapper)->Initialize();
    NSLog(@"Initialized");
}

- (void) free
{
    ((PlatformWrapper *)wrapper)->Free();
    NSLog(@"Freed");
}

- (bool) mainLoop
{
    return ((PlatformWrapper *)wrapper)->MainLoop();
}

- (void) resize:(NSRect)rect
{
    ((PlatformWrapper *)wrapper)->Resize((unsigned)rect.size.width, (unsigned)rect.size.height);
}

- (void) gotFocus
{
    ((PlatformWrapper *)wrapper)->Activate();
}

- (void) lostFocus;
{
    ((PlatformWrapper *)wrapper)->Deactivate();
}

- (AGE::KeyCode) keyCodefromMacKey:(unsigned short)key
{
    switch (key)
    {
        case 0x35: return KEY_ESCAPE;
        case 0x30: return KEY_TAB;
        case 0x32: return KEY_GRAVE;
        case 0x33: return KEY_BACKSPACE;
        case 0x24: return KEY_RETURN;
        case 0x31: return KEY_SPACE;
        case 0x2C: return KEY_SLASH;
        case 0x2A: return KEY_BACKSLASH;
            
        //case 0x: return KEY_SYSRQ; Could be NSF13FunctionKey or NSSysReqFunctionKey or NSPrintScreenFunctionKey so it's not clear how to get it working here.
        case 0x6B: return KEY_SCROLL;
        case 0x71: return KEY_PAUSE;
            
        case 0x72 : return KEY_INSERT;
        case 0x75 : return KEY_DELETE;
        case 0x73 : return KEY_HOME;
        case 0x77 : return KEY_END;
        case 0x74 : return KEY_PGUP;
        case 0x79 : return KEY_PGDN;
            
        case 0x7E: return KEY_UP;
        case 0x7C: return KEY_RIGHT;
        case 0x7B: return KEY_LEFT;
        case 0x7D: return KEY_DOWN;
            
        case 0x12: return KEY_1;
        case 0x13: return KEY_2;
        case 0x14: return KEY_3;
        case 0x15: return KEY_4;
        case 0x17: return KEY_5;
        case 0x16: return KEY_6;
        case 0x1A: return KEY_7;
        case 0x1C: return KEY_8;
        case 0x19: return KEY_9;
        case 0x1D: return KEY_0;
            
        case 0x7A: return KEY_F1;
        case 0x78: return KEY_F2;
        case 0x63: return KEY_F3;
        case 0x76: return KEY_F4;
        case 0x60: return KEY_F5;
        case 0x61: return KEY_F6;
        case 0x62: return KEY_F7;
        case 0x64: return KEY_F8;
        case 0x65: return KEY_F9;
        case 0x6D: return KEY_F10;
        case 0x67: return KEY_F11;
        case 0x6F: return KEY_F12;
            
        case 0x0C: return KEY_Q;
        case 0x0D: return KEY_W;
        case 0x0E: return KEY_E;
        case 0x0F: return KEY_R;
        case 0x11: return KEY_T;
        case 0x10: return KEY_Y;
        case 0x20: return KEY_U;
        case 0x22: return KEY_I;
        case 0x1F: return KEY_O;
        case 0x23: return KEY_P;
        case 0x00: return KEY_A;
        case 0x01: return KEY_S;
        case 0x02: return KEY_D;
        case 0x03: return KEY_F;
        case 0x05: return KEY_G;
        case 0x04: return KEY_H;
        case 0x26: return KEY_J;
        case 0x28: return KEY_K;
        case 0x25: return KEY_L;
        case 0x06: return KEY_Z;
        case 0x07: return KEY_X;
        case 0x08: return KEY_C;
        case 0x09: return KEY_V;
        case 0x0B: return KEY_B;
        case 0x2D: return KEY_N;
        case 0x2E: return KEY_M;
            
        case 0x1B: return KEY_MINUS;
        case 0x18: return KEY_PLUS;
        case 0x21: return KEY_LBRACKET;
        case 0x1E: return KEY_RBRACKET;
            
        case 0x29: return KEY_SEMICOLON;
        case 0x27: return KEY_APOSTROPHE;
            
        case 0x2B: return KEY_COMMA;
        case 0x2F: return KEY_PERIOD;
            
        case 0x52: return KEY_NUMPAD0;
        case 0x53: return KEY_NUMPAD1;
        case 0x54: return KEY_NUMPAD2;
        case 0x55: return KEY_NUMPAD3;
        case 0x56: return KEY_NUMPAD4;
        case 0x57: return KEY_NUMPAD5;
        case 0x58: return KEY_NUMPAD6;
        case 0x59: return KEY_NUMPAD7;
        case 0x5B: return KEY_NUMPAD8;
        case 0x5C: return KEY_NUMPAD9;
        case 0x41: return KEY_NUMPADPERIOD;
        case 0x4C: return KEY_NUMPADENTER;
        case 0x43: return KEY_NUMPADSTAR;
        case 0x45: return KEY_NUMPADPLUS;
        case 0x4E: return KEY_NUMPADMINUS;
        case 0x4B: return KEY_NUMPADSLASH;
        case 0x47: return KEY_NUMLOCK;
            
        default:
            return KEY_UNKNOWN;
    }
}

- (void) setKey:(unsigned short)key status:(bool)down
{
    ((PlatformWrapper *)wrapper)->SetKey([self keyCodefromMacKey:key], down);
}

- (void) setKeyFlags:(NSUInteger)mask
{
    if ((mask & NSEventModifierFlagCapsLock) && !(keyMask & NSEventModifierFlagCapsLock))
    {
        keyMask |= NSEventModifierFlagCapsLock;
        ((PlatformWrapper *)wrapper)->SetKey(KEY_CAPSLOCK, true);
    }
    else
        if (!(mask & NSEventModifierFlagCapsLock) && (keyMask & NSEventModifierFlagCapsLock))
        {
            keyMask ^= NSEventModifierFlagCapsLock;
            ((PlatformWrapper *)wrapper)->SetKey(KEY_CAPSLOCK, false);
        }
        else
            if ((mask & NSEventModifierFlagShift) && !(keyMask & NSEventModifierFlagShift))
            {
                keyMask |= NSEventModifierFlagShift;
                ((PlatformWrapper *)wrapper)->SetKey(KEY_LSHIFT, true);
                ((PlatformWrapper *)wrapper)->SetKey(KEY_RSHIFT, true);
            }
            else
                if (!(mask & NSEventModifierFlagShift) && (keyMask & NSEventModifierFlagShift))
                {
                    keyMask ^= NSEventModifierFlagShift;
                    ((PlatformWrapper *)wrapper)->SetKey(KEY_LSHIFT, false);
                    ((PlatformWrapper *)wrapper)->SetKey(KEY_RSHIFT, false);
                }
                else
                    if ((mask & NSEventModifierFlagControl) && !(keyMask & NSEventModifierFlagControl))
                    {
                        keyMask |= NSEventModifierFlagControl;
                        ((PlatformWrapper *)wrapper)->SetKey(KEY_LCONTROL, true);
                        ((PlatformWrapper *)wrapper)->SetKey(KEY_RCONTROL, true);
                    }
                    else
                        if (!(mask & NSEventModifierFlagControl) && (keyMask & NSEventModifierFlagControl))
                        {
                            keyMask ^= NSEventModifierFlagControl;
                            ((PlatformWrapper *)wrapper)->SetKey(KEY_LCONTROL, false);
                            ((PlatformWrapper *)wrapper)->SetKey(KEY_RCONTROL, false);
                        }
                        else
                            if ((mask & NSEventModifierFlagOption) && !(keyMask & NSEventModifierFlagOption))
                            {
                                keyMask |= NSEventModifierFlagOption;
                                ((PlatformWrapper *)wrapper)->SetKey(KEY_LALT, true);
                                ((PlatformWrapper *)wrapper)->SetKey(KEY_RALT, true);
                            }
                            else
                                if (!(mask & NSEventModifierFlagOption) && (keyMask & NSEventModifierFlagOption))
                                {
                                    keyMask ^= NSEventModifierFlagOption;
                                    ((PlatformWrapper *)wrapper)->SetKey(KEY_LALT, false);
                                    ((PlatformWrapper *)wrapper)->SetKey(KEY_RALT, false);
                                }
                                else
                                    if ((mask & NSEventModifierFlagCommand) && !(keyMask & NSEventModifierFlagCommand))
                                    {
                                        keyMask |= NSEventModifierFlagCommand;
                                        ((PlatformWrapper *)wrapper)->SetKey(KEY_LWIN_OR_CMD, true);
                                        ((PlatformWrapper *)wrapper)->SetKey(KEY_RWIN_OR_CMD, true);
                                    }
                                    else
                                        if (!(mask & NSEventModifierFlagCommand) && (keyMask & NSEventModifierFlagCommand))
                                        {
                                            keyMask ^= NSEventModifierFlagCommand;
                                            ((PlatformWrapper *)wrapper)->SetKey(KEY_LWIN_OR_CMD, false);
                                            ((PlatformWrapper *)wrapper)->SetKey(KEY_RWIN_OR_CMD, false);
                                        }
}

- (void) inputCharacter:(unichar)c
{
    //if ([alphanumeric characterIsMember:c] || [punctuation characterIsMember:c] || [symbol characterIsMember:c] || c == 0x20/*space*/)
    // To implement text input handling here in future.
}

- (void) setLeftMouseButton:(bool)pressed
{
    ((PlatformWrapper *)wrapper)->MouseButton(PlatformWrapper::Left, pressed);
}

- (void) setRightMouseButton:(bool)pressed
{
    ((PlatformWrapper *)wrapper)->MouseButton(PlatformWrapper::Right, pressed);
}

- (void) setMouseWheel:(int)pos
{
    ((PlatformWrapper *)wrapper)->MouseWheel(pos);
}

- (void) setMousePosition:(NSPoint)pos
{
    ((PlatformWrapper *)wrapper)->MouseMove((int)pos.x, (int)pos.y);
}

- (void) fatalAlert:(NSString *)message
{
    NSLog(@"%@", message);
    
    NSAlert *alert = [[NSAlert alloc] init];
    [alert addButtonWithTitle:@"OK"];
    [alert setMessageText:@"Fatal Error"];
    [alert setInformativeText:message];
    [alert setAlertStyle:NSAlertStyleCritical];
    
    if ([alert runModal] == NSAlertFirstButtonReturn)
        [NSApp terminate:self];
    
    [alert release];
}

- (void) toggleCursorVisiblity:(bool)visible
{
    if (visible)
        [NSCursor unhide];
    else
        [NSCursor hide];
}

- (void) reconfigureWindow
{
    [appDelegate reconfigureWindow];
}

void ToggleCursorVisiblity(void *objId, bool visible)
{
    [(id)objId toggleCursorVisiblity:visible];
}

void ReconfigureWindow(void *objId)
{
    [(id)objId reconfigureWindow];
}

void FatalAlert(void *objId, const char *message)
{
    [(id)objId fatalAlert:[NSString stringWithUTF8String:message]];
}

@end
