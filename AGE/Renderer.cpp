#include "Renderer.hpp"
#include "RendererGL.hpp"

using namespace AGE;

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

void Renderer::SetDefaultState()
{
}

void Renderer::SetViewport(int x, int y, unsigned width, unsigned height)
{
}

void Renderer::Clear(bool color, bool depth, bool stencil)
{
}
