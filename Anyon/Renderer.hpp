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
        enum class VertexAttributeIndex { Position, TextureUV, Normal, Tangent };
        
        struct VertexAttributes
        {
            bool textureUV;
            bool normal;
            bool tangent;
        };
        
        class Renderable
        {
            friend class Renderer;
            
        public:
            virtual VertexAttributes VertexAttributes() const = 0;
            virtual unsigned TrianglesCount() const = 0;
            virtual ~Renderable() {};
            
        protected:
            virtual uint8_t* BatchRender() const = 0; // If NULL is returned than batch render is unsupported for the object.
            virtual void InstantRender() const = 0;
        };
        
        class RenderObject
        {
            friend class Renderer;
            
        public:
            enum class ObjectType { Shader, Mesh };
            virtual ObjectType Type() const = 0;
            
        protected:
#ifdef ANYON_GL
            virtual GLuint Object() const = 0;
#endif
        };
        
        void SetDefaultStates();
        void Clear(bool color, bool depth, bool stencil);
        void ClearColor(const Color &col);
        Color ClearColor();
        void Render(Renderable *rend);
        void Bind(RenderObject *obj);
        
        Renderer(Renderer const &) = delete;
        Renderer& operator = (Renderer const &) = delete;
        Renderer& operator = (Renderer &&) = delete;
        
    private:
        ~Renderer() {};
        Renderer() {};
        
        Color colorClear = colorNone;
        unsigned drawCalls, trianglesRendered;
        class Shader *currentShader = nullptr;
        
        void PrepareFrame();
        void CompleteFrame();
        void ResizeViewport(unsigned width, unsigned height);
        
#ifdef ANYON_GL
        GLuint currentVao, currentProgram;
#endif
    };
}
