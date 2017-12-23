#pragma once

#include "types.hpp"
#include "ResourceManager.hpp"
#include "Renderer.hpp"

namespace Anyon
{
    class Mesh : public ResourceManager::Resource, public Renderer::Renderable, public Renderer::StateObject
    {
    public:
        enum class CommonShapes { Quad };
                
        bool Valid() const final;
        ObjectType Type() const final;
        
        Renderer::VertexAttributes VertexAttributes() const final;
        unsigned TrianglesCount() const final;
        
        Mesh(const std::string &name, CommonShapes shape, ResourceManager *resMan);
        Mesh(const std::string &name, const Vector2 *vertices, const Vector2 *uvs, unsigned verticesCount, ResourceManager *resMan);
        //Mesh(const std::string &name, const Vector3 *vertices, const Vector2 *uvs, const Vector3 *normals, const Vector4 *tangents, unsigned verticesCount, ResourceManager *resMan);
        //Mesh(const std::string &name, const Vector3 *vertices, const Vector2 *uvs, const Vector3 *normals, const Vector4 *tangents, const unsigned *indices, unsigned verticesCount, ResourceManager *resMan);
        ~Mesh();
        
    private:
        uint8_t* BatchRender() const final;
        void InstantRender() const final;
        void Create(const uint8_t *data, bool vertices2d, unsigned vertexOffset, unsigned uvOffset, unsigned normalOffset, unsigned tangentOffset, unsigned indicesOffset, unsigned verticesCount);
        
        uint8_t *data = nullptr;
        bool valid = false;
        Renderer::VertexAttributes attribs;
        unsigned vertexSize = 0,
        dataSize = 0,
        verticesCount = 0,
        trianglesCount = 0;
#ifdef ANYON_GL
        GLuint vaoMesh = 0,
        vboVertices = 0,
        vboIndices = 0;
        GLuint Object() const final;
#endif 
    };
}
