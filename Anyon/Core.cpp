#include "Core.hpp"
#include <cassert>
#include "utils.hpp"

using namespace Anyon;
using namespace std;
using namespace chrono;

Core* Core::Application::Core() const
{
    return core;
}

Core::Configuration Core::config;

Core::Core(Application *app):
app(app)
{
    memset(&keys, 0, 256);
    app->core = this;
}

class ResourceManager* Core::ResourceManager()
{
    return &resMan;
}

Renderer* Core::Renderer()
{
    return &renderer;
}

void Core::Initialize()
{
    renderer.SetDefaultStates();
    
    app->Initiaize();
    
    auto time = GetPerfTimer<milliseconds>();
    lastUpdateTime = time;
    lastFpsTime = time;
    fpsCount = 0;
}

void Core::Finalize()
{
    app->Finalize();
    resMan.ReleaseAll();
}

bool Core::MainLoop()
{
    const auto time = GetPerfTimer<milliseconds>();
    
    if (time - lastFpsTime >= 1s)
    {
        fps = fpsCount;
        fpsCount = 0;
        lastFpsTime = time;
    }
    
    if (!Pause)
    {
        renderer.PrepareFrame();
        renderer.Clear(true, true, true);
        app->Update((time - lastUpdateTime).count() / 1000.0);
        renderer.CompleteFrame();
    }
    
    lastUpdateTime = time;
    ++fpsCount;
    
    return !stopFlag;
}

void Core::Resize(unsigned width, unsigned height)
{
    renderer.ResizeViewport(width, height);
}

void Core::Activate()
{
    app->Activate();
}

void Core::Deactivate()
{
    app->Deactivate();
}

void Core::SetKey(KeyCode key, bool pressed)
{
    keys[(uint8_t)key] = pressed;
}

void Core::InputCharacter(wchar_t c)
{
    if (grabTextInput)
        textInput.push_back(c);
}

void Core::MouseMove(int x, int y)
{
    mouse.x = x;
    mouse.y = y;
}

void Core::MouseButton(enum MouseButton button, bool pressed)
{
    switch (button)
    {
        case MouseButton::Left:
            mouse.left = pressed;
            break;
        case MouseButton::Right:
            mouse.right = pressed;
            break;
    }
}

void Core::MouseWheel(int delta)
{
    mouse.wheelDelta = delta;
}

Core* Core::Start(Application *app)
{
    assert(app != nullptr);
    static Core inst(app);
    return &inst;
}

void Core::Stop()
{
    stopFlag = true;
}

void Core::Reconfigure()
{
    ReconfigureWindow();
}

unsigned Core::Fps() const
{
    return fps;
}

void Core::FatalError(const std::string &message)
{
    FatalAlert(message.c_str());
}

Mouse Core::MouseState() const
{
    return mouse;
}

bool Core::KeyPressed(KeyCode key) const
{
    return keys[(uint8_t)key];
}

void Core::BeginTextInput()
{
    grabTextInput = true;
    textInput.clear();
}

void Core::EndTextInput()
{
    grabTextInput = false;
}

std::wstring Core::InputedText()
{
    return textInput;
}

void Core::ShowCursor(bool visible)
{
    ToggleCursorVisiblity(visible);
}
