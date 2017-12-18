#pragma once

#include "types.hpp"

namespace Anyon
{
    class Renderer
    {
        friend class RendererGL;
        
    public:
        static Renderer* Instance();
        
        virtual void PrepareQueue();
        virtual void CompleteQueue();
        virtual void SetDefaultStates();
        virtual void SetViewport(int x, int y, unsigned width, unsigned height);
        virtual void Clear(bool color, bool depth, bool stencil);
        virtual void ClearColor(const Color &col);
        virtual Color ClearColor();
        
        enum RendererType { OpenGL4_1Core };
        virtual RendererType UnderlyingRenderer() = 0;
        
        Renderer(Renderer const &) = delete;
        Renderer& operator = (Renderer const &) = delete;
        
    private:
        Color colorClear = ColorClear();
        
        virtual ~Renderer(){};
        Renderer(){};
    };
}
