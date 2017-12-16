#pragma once

namespace Anyon
{
    enum KeyCode : unsigned char;
    
    class PlatformWrapper
    {
    public:
        enum MouseButton {Left, Right};
#ifdef __APPLE__
        void SetInterlayerInstanceId(/*CoreInterlayer*/void *id);
#endif
        virtual void Initialize() = 0;
        virtual void Finalize() = 0;
        virtual bool MainLoop() = 0;
        virtual void Resize(unsigned width, unsigned height) = 0;
        virtual void Activate() = 0;
        virtual void Deactivate() = 0;
        virtual void SetKey(KeyCode key, bool pressed) = 0;
        virtual void MouseMove(int x, int y) = 0;
        virtual void MouseButton(MouseButton button, bool pressed) = 0;
        virtual void MouseWheel(int delta) = 0;
        
    protected:
        void ToggleCursorVisiblity(bool visible);
        void ReconfigureWindow();
        void FatalAlert(const char *message);
        
    private:
#ifdef __APPLE__
        /*CoreInterlayer*/void *interlayerId;
#endif
    };
}
