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

void RendererGL::Clear(bool color, bool depth, bool stencil)
{
    GLbitfield mask = 0;
    
    if (color)
        mask |= GL_COLOR_BUFFER_BIT;
    
    if (depth)
        mask |= GL_DEPTH_BUFFER_BIT;
    
    if (stencil)
        mask |= GL_STENCIL_BUFFER_BIT;
    
    glClear(mask);
}

void RendererGL::UpdateViewport(unsigned width, unsigned height)
{
    glViewport(0, 0, width, height);
}
