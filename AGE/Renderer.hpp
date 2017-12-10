#pragma once

namespace AGE
{
    class Renderer
    {
    public:
        enum RendererType { OpenGL4_1Core };
        
        virtual void Clear(bool color, bool depth, bool stencil) = 0;
        
        virtual RendererType UnderlyingRenderer() = 0;
        
        Renderer();
        virtual ~Renderer();
        
    protected:
        virtual void UpdateViewport(unsigned width, unsigned height) = 0;
    };
}
