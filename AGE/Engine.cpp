#include "Engine.hpp"
#include "Utils.hpp"
#include "RendererGL.hpp"

using namespace AGE;
using namespace std;
using namespace chrono;

Engine::Application::~Application()
{
    engine = nullptr;
}

void Engine::Application::Activate()
{
    engine->Pause = false;
}

void Engine::Application::Deactivate()
{
    engine->Pause = true;
}

AGE::Engine* Engine::Application::Engine() const
{
    return engine;
}

Engine::Configuration Engine::config;

Engine::Engine(Application *app)
{
    memset(&keys, 0, 256);
    memset(&mouse, 0, sizeof(Mouse));
    
    this->app = app;
    this->app->engine = this;
}

Engine::~Engine()
{
    this->app = nullptr;
}

void Engine::Initialize()
{
    renderer = new RendererGL();
    
    app->Initiaize();
    
    auto time = GetPerfTimer<milliseconds>();
    lastUpdateTime = time;
    lastFpsTime = time;
    fpsCount = 0;
}

void Engine::Free()
{
    app->Free();
    
    delete renderer;
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
        renderer->Clear(true, true, true);
        app->Update((time - lastUpdateTime).count() / 1000.0);
    }
    
    lastUpdateTime = time;
    ++fpsCount;
    
    return !stopFlag;
}

void Engine::Resize(unsigned width, unsigned height)
{
    ((RendererGL *)renderer)->UpdateViewport(width, height);
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

PlatformWrapper* Engine::Start(Application *app)
{
    static Engine engine(app);
    return &engine;
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

Renderer* Engine::Renderer()
{
    return renderer;
}
