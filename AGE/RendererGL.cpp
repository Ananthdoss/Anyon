#include "RendererGL.hpp"
#include "Utils.hpp"

using namespace AGE;

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
}

void RendererGL::CompleteQueue()
{
}
void RendererGL::SetDefaultState()
{
}

void RendererGL::Clear(bool color, bool depth, bool stencil)
{
    glClear((color ? GL_COLOR_BUFFER_BIT : 0) | (depth ? GL_DEPTH_BUFFER_BIT : 0) | (stencil ? GL_STENCIL_BUFFER_BIT : 0));
}

void RendererGL::SetViewport(int x, int y, unsigned width, unsigned height)
{
    glViewport(x, y, width, height);
}
