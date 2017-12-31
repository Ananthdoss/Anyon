#include "Core.hpp"
#include <cassert>
#include <iostream>
#include "utils.hpp"

using namespace Anyon;
using namespace std;
using namespace chrono;

Core* Core::EventReceiver::Core() const
{
    return core;
}

Core::Core(EventReceiver *main):
mainAppReceiver(main)
{
    memset(&keys, 0, 256);
    mainAppReceiver->core = this;
    mainAppReceiver->PrepareConfiguration(config);
}

class ResourceManager* Core::ResourceManager()
{
    return &resMan;
}

class MemoryManager* Core::MemoryManager()
{
    return &memMan;
}

Renderer* Core::Renderer()
{
    return &renderer;
}

Configuration& Core::GetConfiguration()
{
    return config;
}

void Core::Initialize()
{
    renderer.SetDefaultStates();
    
    mainAppReceiver->Initiaize();
    for (auto l : listeners)
        l->Initiaize();
    
    auto time = GetPerfTimer<milliseconds>();
    lastUpdateTime = time;
    lastFpsTime = time;
    fpsCount = 0;
}

void Core::Finalize()
{
    std::cout << "Average fps:" << fpsAccum / fpsCicles << std::endl;
    mainAppReceiver->Finalize();
    for (auto l : listeners)
        l->Finalize();
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
        
        fpsAccum += fps;
        ++fpsCicles;
    }
    
    if (!Pause)
    {
        renderer.PrepareFrame();
        renderer.Clear(true, true, true);
        const double delta = (time - lastUpdateTime).count() / 1000.0;
        mainAppReceiver->Update(delta);
        for (auto l : listeners)
            l->Update(delta);
        renderer.CompleteFrame();
    }
    
    lastUpdateTime = time;
    ++fpsCount;
    
    return !stopFlag;
}

void Core::Resize(unsigned width, unsigned height)
{
    static unsigned w = 0, h = 0;
    
    if (w == width && h == height)
        return;
    
    w = width;
    h = height;
    
    std::cout << "Configuration:" << Core::config << std::endl;
    
    renderer.ResizeViewport(width, height);
    
    mainAppReceiver->Resize(width, height);
    for (auto l : listeners)
        l->Resize(width, height);
}

void Core::Activate()
{
    mainAppReceiver->Activate();
    for (auto l : listeners)
        l->Activate();
}

void Core::Deactivate()
{
    mainAppReceiver->Deactivate();
    for (auto l : listeners)
        l->Deactivate();
}

void Core::SetKey(KeyCode key, bool pressed)
{
    const bool prev = keys[(uint8_t)key];
    
    keys[(uint8_t)key] = pressed;
    
    if (prev && !pressed)
    {
        mainAppReceiver->KeyUp(key);
        for (auto l : listeners)
            l->KeyUp(key);
    }
    else
    {
        mainAppReceiver->KeyDown(key);
        for (auto l : listeners)
            l->KeyDown(key);
    }
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
    mainAppReceiver->MouseMove((unsigned)x, (unsigned)y);
    for (auto l : listeners)
        l->MouseMove((unsigned)x, (unsigned)y);
}

void Core::MouseButton(enum MouseButton button, bool pressed)
{
    bool prev;
    
    switch (button)
    {
        case MouseButton::Left:
            prev = mouse.left;
            mouse.left = pressed;
            break;
            
        case MouseButton::Right:
            prev = mouse.right;
            mouse.right = pressed;
            break;
    }
    
    if (prev && !pressed)
    {
        mainAppReceiver->MouseButtonUp(button);
        for (auto l : listeners)
            l->MouseButtonUp(button);
    }
    else
    {
        mainAppReceiver->MouseButtonDown(button);
        for (auto l : listeners)
            l->MouseButtonDown(button);
    }
}

void Core::MouseWheel(int delta)
{
    mouse.wheelDelta = delta;
    mainAppReceiver->MouseWheel(delta);
    for (auto l : listeners)
        l->MouseWheel(delta);
}

Core* Core::Start(EventReceiver *main)
{
    assert(main != nullptr); // Main event receiver must be set!
    static Core inst(main);
    return &inst;
}

void Core::Stop()
{
    stopFlag = true;
}

Configuration Core::CurrentConfiguration() const
{
    return config;
}

void Core::Reconfigure(Configuration config)
{
    mainAppReceiver->PrepareConfiguration(config);
    for (auto l : listeners)
        l->PrepareConfiguration(config);
    
    this->config = config;
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

void Core::AddEventListner(EventReceiver *listener)
{
    assert(listener != mainAppReceiver); // Trying to add main listener!
    listener->core = this;
    listeners.push_back(listener);
}

void Core::RemoveEventListner(EventReceiver *listener)
{
    assert(listener != mainAppReceiver); // Trying to remove main listener!
    listeners.erase(std::remove(listeners.begin(), listeners.end(), listener), listeners.end());
}

Mouse Core::MouseState() const
{
    return mouse;
}

Vector2 Core::CursorPosition() const
{
    return Vector2(mouse.x, mouse.y);
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
