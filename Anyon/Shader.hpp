#pragma once

#include <string>
#include <unordered_map>
#include "types.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"

namespace Anyon
{
    class Shader : public ResourceManager::Resource, public Renderer::StateObject
    {
    public:
        struct Properties
        {
            //bool diffuseColor;
            bool diffuseTexture;
            //bool alphaTest;
        };
        
        enum class defaultNameIndex { matrixMVP, diffuseTexture };
        static constexpr char const * defaultNames[] = {"matrixMVP", "diffuseTexture"};
        
        int Index(const std::string &name);
        void Set(int index, float f);
        void Set(int index, int i);
        void Set(int index, const Vector2 &v);
        void Set(int index, const Vector3 &v);
        void Set(int index, const Color &c);
        void Set(int index, const Matrix4 &m);
        
        struct Properties Properties() const;
        Renderer::VertexAttributes CompatibleVertexAttributes() const;
        
        bool Valid() const final;
        ObjectType Type() const final;
        
        Shader(const std::string &name, struct Properties props, ResourceManager *resMan);
        ~Shader();
        
    private:
        bool valid = false;
        struct Properties props;
        std::unordered_map<std::string, int> uniforms;
#ifdef ANYON_GL
        GLuint program = 0;
        GLuint Compile(GLenum type, const std::string &source);
        bool Link();
        bool Validate();
        GLuint Object() const final;
#endif
    };
}
