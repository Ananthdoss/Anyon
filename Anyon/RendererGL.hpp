#pragma once

#include <OpenGL/gl3.h>
#include "Renderer.hpp"

namespace Anyon
{
    class RendererGL : public Renderer
    {
        friend class Renderer;
        
    public:
        void PrepareQueue() final;
        void CompleteQueue() final;
        void SetDefaultStates() final;
        void SetViewport(int x, int y, unsigned width, unsigned height) final;
        void Clear(bool color, bool depth, bool stencil) final;
        void ClearColor(const Color &col) final;
        
        RendererType UnderlyingRenderer() final;
        
        RendererGL(RendererGL const &) = delete;
        RendererGL& operator = (RendererGL const &) = delete;
        
    private:
        RendererGL();
        ~RendererGL();
    };
}

