#include "Renderer.hpp"
#include "RendererGL.hpp"

using namespace Anyon;

Renderer* Renderer::Instance()
{
    static RendererGL instance;
    return &instance;
}


Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::PrepareQueue()
{
}

void Renderer::CompleteQueue()
{
}

void Renderer::SetDefaultStates()
{
    ClearColor(ColorClear());
}

void Renderer::SetViewport(int x, int y, unsigned width, unsigned height)
{
}

void Renderer::Clear(bool color, bool depth, bool stencil)
{
}

void Renderer::ClearColor(const Color &col)
{
    colorClear = col;
}

Color Renderer::ClearColor()
{
    return colorClear;
}

