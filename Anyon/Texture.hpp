#pragma once

#include "ResourceManager.hpp"
#include "Renderer.hpp"

namespace Anyon
{
    class Texture: public ResourceManager::Resource, public Renderer::RenderObject
    {
    public:
        enum class PixelFormat { RGB8, RGBA8 };
        enum class FilteringMode { Linear, Bilinear, Trilinear };
        
        bool Valid() const final;
        ObjectType Type() const final;
        
        Texture(const std::string &name, const uint8_t *data, unsigned width, unsigned height, PixelFormat format, FilteringMode mode, bool generateMipmap, bool repeat, ResourceManager *resMan);
        ~Texture();
        
        unsigned Width() const;
        unsigned Height() const;
        PixelFormat Format() const;
        FilteringMode Mode() const;
        
    private:
        unsigned width, height;
        PixelFormat format;
        FilteringMode mode;
#ifdef ANYON_GL
        GLuint texture = 0;
        GLuint Object() const final;
#endif
    };
}
