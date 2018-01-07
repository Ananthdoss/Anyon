#include "Texture.hpp"
#include <cassert>

using namespace Anyon;

bool Texture::Valid() const
{
    return texture != 0;
}

Renderer::RenderObject::ObjectType Texture::Type() const
{
    return Renderer::RenderObject::ObjectType::Texture;
}

Texture::Texture(const std::string &name, const uint8_t *data, unsigned width, unsigned height, PixelFormat format, FilteringMode mode, bool generateMipmap, bool repeat, ResourceManager *resMan):
ResourceManager::Resource(name, resMan), width(width), height(height), format(format), mode(mode)
{
    assert(data != nullptr && width != 0 && height != 0); // Data must be presented!
    
    GLint texCurrent;
    glGetIntegerv(GL_TEXTURE_BINDING_2D, &texCurrent);
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexImage2D(GL_TEXTURE_2D, 0, format == PixelFormat::RGB8 ? GL_RGB8 : GL_RGBA8, width, height, 0, format == PixelFormat::RGB8 ? GL_RGB : GL_RGBA, GL_UNSIGNED_BYTE, data);
    
    if (generateMipmap)
        glGenerateMipmap(GL_TEXTURE_2D);
    
    switch (mode)
    {
        case FilteringMode::Linear:
            if (generateMipmap)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
            else
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            break;
        case FilteringMode::Bilinear:
            if (generateMipmap)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
            else
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
        case FilteringMode::Trilinear:
            if (generateMipmap)
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            else
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            break;
    }
    
    if (repeat)
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }
    else
    {
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    }
    
    glBindTexture(GL_TEXTURE_2D, texCurrent);
}

Texture::~Texture()
{
    glDeleteTextures(1, &texture);
}

unsigned Texture::Width() const
{
    return width;
}

unsigned Texture::Height() const
{
    return height;
}

Texture::PixelFormat Texture::Format() const
{
    return format;
}

Texture::FilteringMode Texture::Mode() const
{
    return mode;
}

GLuint Texture::Object() const
{
    return texture;
}
