#include <cassert>
#include "Engine.hpp"
#include "utils.hpp"
#include "Renderer.hpp"

using namespace Anyon;
using namespace std;
using namespace chrono;

Engine::Configuration Engine::config;

Engine* Engine::Instance()
{
    static Engine instance;
    return &instance;
}

Engine::Engine()
{
    memset(&keys, 0, 256);
    memset(&mouse, 0, sizeof(Mouse));
}

void Engine::Initialize()
{
    app->Initiaize();
    
    auto time = GetPerfTimer<milliseconds>();
    lastUpdateTime = time;
    lastFpsTime = time;
    fpsCount = 0;
}

void Engine::Finalize()
{
    app->Finalize();
}

bool Engine::MainLoop()
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

void Engine::Resize(unsigned width, unsigned height)
{
    Renderer::Instance()->SetViewport(0, 0, width, height);
}

void Engine::Activate()
{
    app->Activate();
}

void Engine::Deactivate()
{
    app->Deactivate();
}

void Engine::SetKey(KeyCode key, bool pressed)
{
    keys[key] = pressed;
}

void Engine::MouseMove(int x, int y)
{
    mouse.x = x;
    mouse.y = y;
}

void Engine::MouseButton(enum MouseButton button, bool pressed)
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

void Engine::MouseWheel(int delta)
{
    mouse.wheel = delta;
}

void Engine::Start(Application *app)
{
    assert(app != nullptr && app != this->app);
    this->app = app;
}

void Engine::Stop()
{
    stopFlag = true;
}

void Engine::Reconfigure()
{
    ReconfigureWindow();
}

unsigned Engine::Fps() const
{
    return fps;
}

void Engine::FatalError(const std::string &message)
{
    FatalAlert(message.c_str());
}

Mouse Engine::MouseState() const
{
    return mouse;
}

bool Engine::KeyPressed(KeyCode key) const
{
    return keys[key];
}

void Engine::ShowCursor(bool visible)
{
    ToggleCursorVisiblity(visible);
}

