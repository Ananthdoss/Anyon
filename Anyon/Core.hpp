#pragma once

#include <string>
#include <chrono>
#include <vector>
#include "PlatformWrapper.hpp"
#include "Renderer.hpp"
#include "ResourceManager.hpp"
#include "MemoryManager.hpp"

namespace Anyon
{
    class Renderer;
    
    enum class KeyCode : uint8_t;
    
    struct Mouse
    {
        int x, y,
        wheelDelta;
        bool left, right;
        
        Mouse():
        x(0), y(0), wheelDelta(0), left(false), right(false) {}
    };
    
    struct Configuration
    {
        unsigned width = -1; // half of native screen width
        unsigned height = -1; // same as width
        bool fullscreen = false;
        bool vsync = true;
        bool fsaa = true;
        
        friend std::ostream& operator << (std::ostream &stream, const Configuration &config)
        {
            stream << config.width << "x" << config.height << (config.fullscreen ? " fullscreen" : " ") << (config.vsync ? " vsync" : " ") <<  (config.fsaa ? " fsaa" : " ");
            return stream;
        }
    };
    
    class Core : private PlatformWrapper
    {
    public:
        
        class EventReceiver
        {
            friend class Core;
            
        public:
            virtual void Initiaize() = 0;
            virtual void Finalize() = 0;
            virtual void Update(const double delta) = 0;
            virtual void PrepareConfiguration(Configuration &config) {};
            virtual void Activate() {};
            virtual void Deactivate() {};
            virtual void Resize(unsigned width, unsigned height) {};
            virtual void KeyUp(KeyCode key) {};
            virtual void KeyDown(KeyCode key) {};
            virtual void MouseMove(unsigned x, unsigned y) {};
            virtual void MouseButtonUp(enum MouseButton button) {};
            virtual void MouseButtonDown(enum MouseButton button) {};
            virtual void MouseWheel(int delta) {};
            
            virtual ~EventReceiver() {};
            
        protected:
            Core* Core() const;
            
        private:
            class Core *core;
        };
        
        static Core* Start(EventReceiver *main);
        
        void Stop();
        bool Pause = false;
        Configuration CurrentConfiguration() const;
        void Reconfigure(Configuration config);
        unsigned Fps() const;
        void FatalError(const std::string &message);
        void AddEventListner(EventReceiver *listener);
        void RemoveEventListner(EventReceiver *listener);
        
        Mouse MouseState() const;
        Vector2 CursorPosition() const;
        bool KeyPressed(KeyCode key) const;
        void BeginTextInput();
        void EndTextInput();
        std::wstring InputedText();
        void ShowCursor(bool visible);
        
        class ResourceManager* ResourceManager();
        class MemoryManager* MemoryManager();
        class Renderer* Renderer();
        
        Core(Core const &) = delete;
        Core& operator = (Core const &) = delete;
        Core& operator = (Core &&) = delete;
        
    private:
        Configuration config;
        EventReceiver *mainAppReceiver = nullptr;
        std::vector<EventReceiver*> listeners;
        
        class Renderer renderer;
        class ResourceManager resMan;
        class MemoryManager memMan;
        
        bool stopFlag = false;
        bool keys[256];
        std::wstring textInput;
        bool grabTextInput = false;
        Mouse mouse;
        
        std::chrono::milliseconds lastUpdateTime;
        std::chrono::milliseconds lastFpsTime;
        unsigned fpsCount, fps = 0,
        fpsAccum = 0, fpsCicles = 0;
        
        Core(EventReceiver *main);
        ~Core(){};
        
        Configuration& GetConfiguration() final;
        void Initialize() final;
        void Finalize() final;
        bool MainLoop() final;
        void Resize(unsigned width, unsigned height) final;
        void Activate() final;
        void Deactivate() final;
        void SetKey(KeyCode key, bool pressed) final;
        void InputCharacter(wchar_t c) final;
        void MouseMove(int x, int y) final;
        void MouseButton(enum MouseButton button, bool pressed) final;
        void MouseWheel(int delta) final;
    };
    
    enum class KeyCode : uint8_t
    {
        KEY_UNKNOWN         = 0x00,
        KEY_ESCAPE          = 0x01,
        KEY_TAB             = 0x0F,
        KEY_GRAVE           = 0x29,
        KEY_CAPSLOCK        = 0x3A,
        KEY_BACKSPACE       = 0x0E,
        KEY_RETURN          = 0x1C,
        KEY_SPACE           = 0x39,
        KEY_SLASH           = 0x35,
        KEY_BACKSLASH       = 0x2B,
        
        KEY_SYSRQ           = 0xB7,
        KEY_SCROLL          = 0x46,
        KEY_PAUSE           = 0xC5,
        
        KEY_INSERT          = 0xD2,
        KEY_DELETE          = 0xD3,
        KEY_HOME            = 0xC7,
        KEY_END             = 0xCF,
        KEY_PGUP            = 0xC9,
        KEY_PGDN            = 0xD1,
        
        KEY_LSHIFT          = 0x2A,
        KEY_RSHIFT          = 0x36,
        KEY_LALT            = 0x38,
        KEY_RALT            = 0xB8,
        KEY_LWIN_OR_CMD     = 0xDB,
        KEY_RWIN_OR_CMD     = 0xDC,
        KEY_LCONTROL        = 0x1D,
        KEY_RCONTROL        = 0x9D,
        
        KEY_UP              = 0xC8,
        KEY_RIGHT           = 0xCD,
        KEY_LEFT            = 0xCB,
        KEY_DOWN            = 0xD0,
        
        KEY_1               = 0x02,
        KEY_2               = 0x03,
        KEY_3               = 0x04,
        KEY_4               = 0x05,
        KEY_5               = 0x06,
        KEY_6               = 0x07,
        KEY_7               = 0x08,
        KEY_8               = 0x09,
        KEY_9               = 0x0A,
        KEY_0               = 0x0B,
        
        KEY_F1              = 0x3B,
        KEY_F2              = 0x3C,
        KEY_F3              = 0x3D,
        KEY_F4              = 0x3E,
        KEY_F5              = 0x3F,
        KEY_F6              = 0x40,
        KEY_F7              = 0x41,
        KEY_F8              = 0x42,
        KEY_F9              = 0x43,
        KEY_F10             = 0x44,
        KEY_F11             = 0x57,
        KEY_F12             = 0x58,
        
        KEY_Q               = 0x10,
        KEY_W               = 0x11,
        KEY_E               = 0x12,
        KEY_R               = 0x13,
        KEY_T               = 0x14,
        KEY_Y               = 0x15,
        KEY_U               = 0x16,
        KEY_I               = 0x17,
        KEY_O               = 0x18,
        KEY_P               = 0x19,
        KEY_A               = 0x1E,
        KEY_S               = 0x1F,
        KEY_D               = 0x20,
        KEY_F               = 0x21,
        KEY_G               = 0x22,
        KEY_H               = 0x23,
        KEY_J               = 0x24,
        KEY_K               = 0x25,
        KEY_L               = 0x26,
        KEY_Z               = 0x2C,
        KEY_X               = 0x2D,
        KEY_C               = 0x2E,
        KEY_V               = 0x2F,
        KEY_B               = 0x30,
        KEY_N               = 0x31,
        KEY_M               = 0x32,
        
        KEY_MINUS           = 0x0C,
        KEY_PLUS            = 0x0D,
        KEY_LBRACKET        = 0x1A,
        KEY_RBRACKET        = 0x1B,
        
        KEY_SEMICOLON       = 0x27,
        KEY_APOSTROPHE      = 0x28,
        
        KEY_COMMA           = 0x33,
        KEY_PERIOD          = 0x34,
        
        KEY_NUMPAD0         = 0x52,
        KEY_NUMPAD1         = 0x4F,
        KEY_NUMPAD2         = 0x50,
        KEY_NUMPAD3         = 0x51,
        KEY_NUMPAD4         = 0x4B,
        KEY_NUMPAD5         = 0x4C,
        KEY_NUMPAD6         = 0x4D,
        KEY_NUMPAD7         = 0x47,
        KEY_NUMPAD8         = 0x48,
        KEY_NUMPAD9         = 0x49,
        KEY_NUMPADPERIOD    = 0x53,
        KEY_NUMPADENTER     = 0x9C,
        KEY_NUMPADSTAR      = 0x37,
        KEY_NUMPADPLUS      = 0x4E,
        KEY_NUMPADMINUS     = 0x4A,
        KEY_NUMPADSLASH     = 0xB5,
        KEY_NUMLOCK         = 0x45
    };
}
