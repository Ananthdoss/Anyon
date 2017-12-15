#include "RendererGL.hpp"
#include "utils.hpp"

using namespace Anyon;

RendererGL::RendererGL()
{
}

RendererGL::~RendererGL()
{
}

Renderer::RendererType RendererGL::UnderlyingRenderer()
{
    return OpenGL4_1Core;
}

void RendererGL::PrepareQueue()
{
    Renderer::PrepareQueue();
}

void RendererGL::CompleteQueue()
{
    Renderer::CompleteQueue();
}

void RendererGL::SetDefaultStates()
{
    Renderer::SetDefaultStates();
}

void RendererGL::SetViewport(int x, int y, unsigned width, unsigned height)
{
    Renderer::SetViewport(x, y, width, height);
    glViewport(x, y, width, height);
}

void RendererGL::Clear(bool color, bool depth, bool stencil)
{
    Renderer::Clear(color, depth, stencil);
    glClear((color ? GL_COLOR_BUFFER_BIT : 0) | (depth ? GL_DEPTH_BUFFER_BIT : 0) | (stencil ? GL_STENCIL_BUFFER_BIT : 0));
}

void RendererGL::ClearColor(const Color &col)
{
    Renderer::ClearColor(col);
    glClearColor(col.r, col.g, col.b, col.a);
}

