#include <cassert>
#include "Core.hpp"
#include "utils.hpp"
#include "Renderer.hpp"

using namespace Anyon;
using namespace std;
using namespace chrono;

Core::Configuration Core::config;

Core* Core::Instance()
{
    static Core instance;
    return &instance;
}

Core::Core()
{
    memset(&keys, 0, 256);
    memset(&mouse, 0, sizeof(Mouse));
}

void Core::Initialize()
{
    Renderer::Instance()->SetDefaultStates();
    
    app->Initiaize();
    
    auto time = GetPerfTimer<milliseconds>();
    lastUpdateTime = time;
    lastFpsTime = time;
    fpsCount = 0;
}

void Core::Finalize()
{
    app->Finalize();
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
        auto *r = Renderer::Instance();
        r->CompleteQueue();
        r->Clear(true, true, true);
        app->Update((time - lastUpdateTime).count() / 1000.0);
        r->CompleteQueue();
    }
    
    lastUpdateTime = time;
    ++fpsCount;
    
    return !stopFlag;
}

void Core::Resize(unsigned width, unsigned height)
{
    Renderer::Instance()->SetViewport(0, 0, width, height);
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
    keys[key] = pressed;
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
        case Left:
            mouse.left = pressed;
            break;
        case Right:
            mouse.right = pressed;
            break;
    }
}

void Core::MouseWheel(int delta)
{
    mouse.wheel = delta;
}

void Core::Start(Application *app)
{
    assert(app != nullptr && app != this->app);
    this->app = app;
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
    return keys[key];
}

void Core::ShowCursor(bool visible)
{
    ToggleCursorVisiblity(visible);
}

