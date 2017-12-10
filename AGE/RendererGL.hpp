#pragma once

#include <OpenGL/gl3.h>
#include "Renderer.hpp"

namespace AGE
{
    class RendererGL : public Renderer
    {
    public:
        void Clear(bool color, bool depth, bool stencil) final;
        void UpdateViewport(unsigned width, unsigned height) final;
        
        RendererType UnderlyingRenderer() final;
        
        RendererGL();
        ~RendererGL();
    };
}
