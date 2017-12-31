#include "Renderer.hpp"
#include <cassert>
#include "utils.hpp"
#include "Core.hpp"
#include "Shader.hpp"

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
    glViewport(0, 0, width, height);
}

void Renderer::SetDefaultStates()
{
    // Research if this is necessary and could it slow working with textures?
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glPixelStorei(GL_PACK_ALIGNMENT, 1);
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    
    currentVao = 0;
    glBindVertexArray(0);
    
    currentShader = nullptr;
    currentProgram = 0;
    glUseProgram(0);
    
    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    currentTextures[(unsigned)TextureLayer::Diffuse] = 0;
    glBindTexture(GL_TEXTURE_2D, 0);
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
    assert(currentShader != nullptr); // Rendering will have no result if no shader is set!
    
    RenderObject *so = dynamic_cast<RenderObject*>(rend);
    assert(so != NULL); // Every Renderable class must be derived from RenderObject class!
    Bind(so);
    
    assert(currentShader == nullptr || currentShader->CompatibleWith(rend->VertexAttributes())); // Current shader is incompatible with given geometry!
    
    assert(currentShader == nullptr || currentShader->Properties().diffuseTexture == currentTextures[(unsigned)TextureLayer::Diffuse] != 0); // Texture must be set for this shader!
    
    rend->InstantRender();
    
    ++drawCalls;
    trianglesRendered += rend->TrianglesCount();
}

void Renderer::Bind(RenderObject *obj)
{
    const GLuint o = obj->Object();
    
    switch (obj->Type()) {
        case RenderObject::ObjectType::Shader:
            if (o != currentProgram)
            {
                Shader *s = dynamic_cast<Shader*>(obj);
                assert(s != NULL); // Object of type Shader must be of the same class!
                currentShader = s;
                currentProgram = o;
                glUseProgram(o);
            }
            break;
            
        case RenderObject::ObjectType::Mesh:
            if (o != currentVao)
            {
                currentVao = o;
                glBindVertexArray(o);
            }
            break;
            
        case RenderObject::ObjectType::Texture:
            if (o != currentTextures[(unsigned)TextureLayer::Diffuse])
            {
                currentTextures[(unsigned)TextureLayer::Diffuse] = o;
                
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, o);
                
                if (currentShader && currentShader->Properties().diffuseTexture)
                    currentShader->Set(currentShader->Index(Shader::defaultNames[(unsigned)Shader::defaultNameIndex::diffuseTexture]), 0);
            }
            break;
    }
}
