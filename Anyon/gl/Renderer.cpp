#include "Renderer.hpp"
#include <cassert>
#include <iostream>
#include "utils.hpp"
#include "Core.hpp"

using namespace Anyon;

void Renderer::PrepareFrame()
{
    drawCalls = 0;
    trianglesRendered = 0;
}

void Renderer::CompleteFrame()
{
}

void Renderer::ResizeViewport(unsigned width, unsigned height)
{
    std::cout << "Configuration:" << Core::config << std::endl;
    glViewport(0, 0, width, height);
}

void Renderer::SetDefaultStates()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    currentVao = 0;
    glBindVertexArray(0);
    
    currentProgram = 0;
    glUseProgram(0);
    
    //glActiveTexture(GL_TEXTURE0);
    //glEnable(GL_TEXTURE_2D);
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

void Renderer::Render(Renderable *rend)
{
    StateObject *so = dynamic_cast<StateObject *>(rend);
    assert(so != NULL); // Every Renderable class must be derived from StateObject class!
    Bind(so);
    
    rend->InstantRender();
    
    ++drawCalls;
    trianglesRendered += rend->TrianglesCount();
}

void Renderer::Bind(StateObject *obj)
{
    const GLuint o = obj->Object();
    
    switch (obj->Type()) {
        case StateObject::ObjectType::Shader:
            if (o != currentProgram)
            {
                currentProgram = o;
                glUseProgram(o);
            }
            break;
            
        case StateObject::ObjectType::Mesh:
            if (o != currentVao)
            {
                currentVao = o;
                glBindVertexArray(o);
            }
            break;
    }
}
