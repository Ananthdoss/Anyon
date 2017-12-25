#import "CoreInterlayer.h"
#import "AppDelegate.h"

#include "../Core.hpp"

using namespace Anyon;

@implementation CoreInterlayer

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
    return ((PlatformWrapper *)wrapper)->GetConfiguration().width;
}

- (void) setConfigWidth:(unsigned) width
{
    ((PlatformWrapper *)wrapper)->GetConfiguration().width = width;
}

- (unsigned) configHeight
{
    return ((PlatformWrapper *)wrapper)->GetConfiguration().height;
}

- (void) setConfigHeight:(unsigned) height
{
    ((PlatformWrapper *)wrapper)->GetConfiguration().height = height;
}

- (bool) configFullscreen
{
    return ((PlatformWrapper *)wrapper)->GetConfiguration().fullscreen;
}

- (bool) configVsync
{
    return ((PlatformWrapper *)wrapper)->GetConfiguration().vsync;
}

- (bool) configFsaa
{
    return ((PlatformWrapper *)wrapper)->GetConfiguration().fsaa;
}

- (void) setConfigFsaa:(bool) fsaa
{
    ((PlatformWrapper *)wrapper)->GetConfiguration().fsaa = fsaa;
}

- (void) initialize
{
    ((PlatformWrapper *)wrapper)->Initialize();
    NSLog(@"Initialized");
}

- (void) finalize
{
    ((PlatformWrapper *)wrapper)->Finalize();
    NSLog(@"Finalized");
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

- (Anyon::KeyCode) keyCodefromMacKey:(unsigned short)key
{
    switch (key)
    {
        case 0x35: return KeyCode::KEY_ESCAPE;
        case 0x30: return KeyCode::KEY_TAB;
        case 0x32: return KeyCode::KEY_GRAVE;
        case 0x33: return KeyCode::KEY_BACKSPACE;
        case 0x24: return KeyCode::KEY_RETURN;
        case 0x31: return KeyCode::KEY_SPACE;
        case 0x2C: return KeyCode::KEY_SLASH;
        case 0x2A: return KeyCode::KEY_BACKSLASH;
            
        case 0x69: return KeyCode::KEY_SYSRQ;
        case 0x6B: return KeyCode::KEY_SCROLL;
        case 0x71: return KeyCode::KEY_PAUSE;
            
        case 0x72 : return KeyCode::KEY_INSERT;
        case 0x75 : return KeyCode::KEY_DELETE;
        case 0x73 : return KeyCode::KEY_HOME;
        case 0x77 : return KeyCode::KEY_END;
        case 0x74 : return KeyCode::KEY_PGUP;
        case 0x79 : return KeyCode::KEY_PGDN;
            
        case 0x7E: return KeyCode::KEY_UP;
        case 0x7C: return KeyCode::KEY_RIGHT;
        case 0x7B: return KeyCode::KEY_LEFT;
        case 0x7D: return KeyCode::KEY_DOWN;
            
        case 0x12: return KeyCode::KEY_1;
        case 0x13: return KeyCode::KEY_2;
        case 0x14: return KeyCode::KEY_3;
        case 0x15: return KeyCode::KEY_4;
        case 0x17: return KeyCode::KEY_5;
        case 0x16: return KeyCode::KEY_6;
        case 0x1A: return KeyCode::KEY_7;
        case 0x1C: return KeyCode::KEY_8;
        case 0x19: return KeyCode::KEY_9;
        case 0x1D: return KeyCode::KEY_0;
            
        case 0x7A: return KeyCode::KEY_F1;
        case 0x78: return KeyCode::KEY_F2;
        case 0x63: return KeyCode::KEY_F3;
        case 0x76: return KeyCode::KEY_F4;
        case 0x60: return KeyCode::KEY_F5;
        case 0x61: return KeyCode::KEY_F6;
        case 0x62: return KeyCode::KEY_F7;
        case 0x64: return KeyCode::KEY_F8;
        case 0x65: return KeyCode::KEY_F9;
        case 0x6D: return KeyCode::KEY_F10;
        case 0x67: return KeyCode::KEY_F11;
        case 0x6F: return KeyCode::KEY_F12;
            
        case 0x0C: return KeyCode::KEY_Q;
        case 0x0D: return KeyCode::KEY_W;
        case 0x0E: return KeyCode::KEY_E;
        case 0x0F: return KeyCode::KEY_R;
        case 0x11: return KeyCode::KEY_T;
        case 0x10: return KeyCode::KEY_Y;
        case 0x20: return KeyCode::KEY_U;
        case 0x22: return KeyCode::KEY_I;
        case 0x1F: return KeyCode::KEY_O;
        case 0x23: return KeyCode::KEY_P;
        case 0x00: return KeyCode::KEY_A;
        case 0x01: return KeyCode::KEY_S;
        case 0x02: return KeyCode::KEY_D;
        case 0x03: return KeyCode::KEY_F;
        case 0x05: return KeyCode::KEY_G;
        case 0x04: return KeyCode::KEY_H;
        case 0x26: return KeyCode::KEY_J;
        case 0x28: return KeyCode::KEY_K;
        case 0x25: return KeyCode::KEY_L;
        case 0x06: return KeyCode::KEY_Z;
        case 0x07: return KeyCode::KEY_X;
        case 0x08: return KeyCode::KEY_C;
        case 0x09: return KeyCode::KEY_V;
        case 0x0B: return KeyCode::KEY_B;
        case 0x2D: return KeyCode::KEY_N;
        case 0x2E: return KeyCode::KEY_M;
            
        case 0x1B: return KeyCode::KEY_MINUS;
        case 0x18: return KeyCode::KEY_PLUS;
        case 0x21: return KeyCode::KEY_LBRACKET;
        case 0x1E: return KeyCode::KEY_RBRACKET;
            
        case 0x29: return KeyCode::KEY_SEMICOLON;
        case 0x27: return KeyCode::KEY_APOSTROPHE;
            
        case 0x2B: return KeyCode::KEY_COMMA;
        case 0x2F: return KeyCode::KEY_PERIOD;
            
        case 0x52: return KeyCode::KEY_NUMPAD0;
        case 0x53: return KeyCode::KEY_NUMPAD1;
        case 0x54: return KeyCode::KEY_NUMPAD2;
        case 0x55: return KeyCode::KEY_NUMPAD3;
        case 0x56: return KeyCode::KEY_NUMPAD4;
        case 0x57: return KeyCode::KEY_NUMPAD5;
        case 0x58: return KeyCode::KEY_NUMPAD6;
        case 0x59: return KeyCode::KEY_NUMPAD7;
        case 0x5B: return KeyCode::KEY_NUMPAD8;
        case 0x5C: return KeyCode::KEY_NUMPAD9;
        case 0x41: return KeyCode::KEY_NUMPADPERIOD;
        case 0x4C: return KeyCode::KEY_NUMPADENTER;
        case 0x43: return KeyCode::KEY_NUMPADSTAR;
        case 0x45: return KeyCode::KEY_NUMPADPLUS;
        case 0x4E: return KeyCode::KEY_NUMPADMINUS;
        case 0x4B: return KeyCode::KEY_NUMPADSLASH;
        case 0x47: return KeyCode::KEY_NUMLOCK;
            
        default:
            return KeyCode::KEY_UNKNOWN;
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
        ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_CAPSLOCK, true);
    }
    else
        if (!(mask & NSEventModifierFlagCapsLock) && (keyMask & NSEventModifierFlagCapsLock))
        {
            keyMask ^= NSEventModifierFlagCapsLock;
            ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_CAPSLOCK, false);
        }
        else
            if ((mask & NSEventModifierFlagShift) && !(keyMask & NSEventModifierFlagShift))
            {
                keyMask |= NSEventModifierFlagShift;
                ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LSHIFT, true);
                ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RSHIFT, true);
            }
            else
                if (!(mask & NSEventModifierFlagShift) && (keyMask & NSEventModifierFlagShift))
                {
                    keyMask ^= NSEventModifierFlagShift;
                    ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LSHIFT, false);
                    ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RSHIFT, false);
                }
                else
                    if ((mask & NSEventModifierFlagControl) && !(keyMask & NSEventModifierFlagControl))
                    {
                        keyMask |= NSEventModifierFlagControl;
                        ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LCONTROL, true);
                        ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RCONTROL, true);
                    }
                    else
                        if (!(mask & NSEventModifierFlagControl) && (keyMask & NSEventModifierFlagControl))
                        {
                            keyMask ^= NSEventModifierFlagControl;
                            ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LCONTROL, false);
                            ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RCONTROL, false);
                        }
                        else
                            if ((mask & NSEventModifierFlagOption) && !(keyMask & NSEventModifierFlagOption))
                            {
                                keyMask |= NSEventModifierFlagOption;
                                ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LALT, true);
                                ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RALT, true);
                            }
                            else
                                if (!(mask & NSEventModifierFlagOption) && (keyMask & NSEventModifierFlagOption))
                                {
                                    keyMask ^= NSEventModifierFlagOption;
                                    ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LALT, false);
                                    ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RALT, false);
                                }
                                else
                                    if ((mask & NSEventModifierFlagCommand) && !(keyMask & NSEventModifierFlagCommand))
                                    {
                                        keyMask |= NSEventModifierFlagCommand;
                                        ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LWIN_OR_CMD, true);
                                        ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RWIN_OR_CMD, true);
                                    }
                                    else
                                        if (!(mask & NSEventModifierFlagCommand) && (keyMask & NSEventModifierFlagCommand))
                                        {
                                            keyMask ^= NSEventModifierFlagCommand;
                                            ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_LWIN_OR_CMD, false);
                                            ((PlatformWrapper *)wrapper)->SetKey(KeyCode::KEY_RWIN_OR_CMD, false);
                                        }
}

- (void) inputCharacter:(unichar)c
{
    if ([alphanumeric characterIsMember:c] || [punctuation characterIsMember:c] || [symbol characterIsMember:c] || c == 0x20/*space*/)
        ((PlatformWrapper *)wrapper)->InputCharacter(c);
}

- (void) setLeftMouseButton:(bool)pressed
{
    ((PlatformWrapper *)wrapper)->MouseButton(PlatformWrapper::MouseButton::Left, pressed);
}

- (void) setRightMouseButton:(bool)pressed
{
    ((PlatformWrapper *)wrapper)->MouseButton(PlatformWrapper::MouseButton::Right, pressed);
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
