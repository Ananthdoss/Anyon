#pragma once

#if defined(ANYON_MAC) && defined(ANYON_GL)
#include <OpenGL/gl3.h>
#endif

#include "types.hpp"

namespace Anyon
{
    class Renderer
    {
        friend class Core;
        
    public:
        void PrepareQueue();
        void CompleteQueue();
        void SetDefaultStates();
        void Clear(bool color, bool depth, bool stencil);
        void ClearColor(const Color &col);
        Color ClearColor();
        
        Renderer(Renderer const &) = delete;
        Renderer& operator = (Renderer const &) = delete;
        Renderer& operator = (Renderer &&) = delete;
        
    private:
        ~Renderer(){};
        Renderer(){};
        
        Color colorClear = colorNone;
        
        void ResizeViewport(unsigned width, unsigned height);
        
#ifdef ANYON_GL
        
#endif
    };
}
