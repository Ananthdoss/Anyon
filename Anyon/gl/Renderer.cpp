#include "Renderer.hpp"
#include "utils.hpp"

using namespace Anyon;

void Renderer::PrepareQueue()
{
}

void Renderer::CompleteQueue()
{
}

void Renderer::SetDefaultStates()
{
}

void Renderer::ResizeViewport(unsigned width, unsigned height)
{
    glViewport(0, 0, width, height);
}

void Renderer::Clear(bool color, bool depth, bool stencil)
{
    glClear((color ? GL_COLOR_BUFFER_BIT : 0) | (depth ? GL_DEPTH_BUFFER_BIT : 0) | (stencil ? GL_STENCIL_BUFFER_BIT : 0));
}

void Renderer::ClearColor(const Color &col)
{
    colorClear = col;
    glClearColor(colorClear.r, colorClear.g, colorClear.b, colorClear.a);
}
