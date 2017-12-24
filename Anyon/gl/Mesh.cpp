#include "Mesh.hpp"
#include <cassert>

using namespace Anyon;

bool Mesh::Valid() const
{
    return valid;
}

Renderer::RenderObject::ObjectType Mesh::Type() const
{
    return ObjectType::Mesh;
}

Renderer::VertexAttributes Mesh::VertexAttributes() const
{
    return attribs;
}

unsigned Mesh::TrianglesCount() const
{
    return trianglesCount;
}

uint8_t* Mesh::BatchRender() const
{
    return data;
}

void Mesh::InstantRender() const
{
    glDrawArrays(GL_TRIANGLES, 0, verticesCount);
}

GLuint Mesh::Object() const
{
    return vaoMesh;
}

Mesh::Mesh(const std::string &name, CommonShapes shape, ResourceManager *resMan):
ResourceManager::Resource(name, resMan)
{
    static GLfloat quad[] = {
      /* position    textureUV */
        -0.5, -0.5,  0.0, 0.0,
         0.5, -0.5,  1.0, 0.0,
        -0.5,  0.5,  0.0, 1.0,
         0.5, -0.5,  1.0, 0.0,
         0.5,  0.5,  1.1, 1.0,
        -0.5,  0.5,  0.0, 1.0
    };
    
    switch (shape)
    {
        case CommonShapes::Quad:
            Create((uint8_t*)quad, true, 0, 2 * sizeof(GLfloat), -1, -1, -1, 6);
            break;
    }
}

Mesh::Mesh(const std::string &name, const Vector2 *vertices, const Vector2 *uvs, unsigned verticesCount, ResourceManager *resMan):
ResourceManager::Resource(name, resMan)
{
    assert(vertices != nullptr && verticesCount > 0); // Vertices must not be empty!
    
    const bool tex = uvs == nullptr;
    const unsigned vsize = verticesCount * 2 + (tex ? 0 : 2);
    
    uint8_t *data = new uint8_t[vsize * sizeof(float)];
    
    for (int i = 0; i < verticesCount; ++i)
    {
        memcpy(&data[vsize * i], vertices[i].xy, 2 * sizeof(float));
        
        if (tex)
            memcpy(&data[vsize * i], uvs[i].xy, 2 * sizeof(float));
    }
    
    Create((uint8_t*)data, true, 0, tex ? 2 * sizeof(GLfloat) : -1, -1, -1, -1, 6);
    
    delete[] data;
}

void Mesh::Create(const uint8_t *data, bool vertices2d, unsigned vertexOffset, unsigned uvOffset, unsigned normalOffset, unsigned tangentOffset, unsigned indicesOffset, unsigned verticesCount)
{
    assert(normalOffset == -1 && tangentOffset == -1 && indicesOffset == -1); // These features are not implemented yet!
    
    assert(data != nullptr && verticesCount != 0); // Data can't be null!
    
    attribs = {uvOffset != -1, normalOffset != -1, tangentOffset != -1};
    
    vertexSize = ((vertices2d ? 2 : 3) + (attribs.textureUV ? 2 : 0) + (attribs.normal ? 3 : 0) + (attribs.tangent ? 4 : 0)) * sizeof(GLfloat);
    assert(vertexOffset < vertexSize && (uvOffset == -1 || uvOffset < vertexSize) && (normalOffset == -1 || normalOffset < vertexSize) && (tangentOffset == -1 || tangentOffset < vertexSize)); // Data must be interlieved!
    
    dataSize = vertexSize * verticesCount;
    assert(indicesOffset == -1 || indicesOffset >= dataSize); // Indices data must be beyond vertices data!
    
    trianglesCount = verticesCount / 3;
    this->verticesCount = verticesCount;
    
    this->data = new uint8_t[dataSize];
    memcpy(this->data, data, dataSize);
    
    GLint vaoCurrent;
    glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &vaoCurrent);
    
    glGenVertexArrays(1, &vaoMesh);
    glBindVertexArray(vaoMesh);
    
    glGenBuffers(1, &vboVertices);
    glBindBuffer(GL_ARRAY_BUFFER, vboVertices);
    glBufferData(GL_ARRAY_BUFFER, dataSize, this->data, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray((GLuint)Renderer::VertexAttributeIndex::Position);
    glVertexAttribPointer((GLuint)Renderer::VertexAttributeIndex::Position, vertices2d ? 2 : 3, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)NULL);
    
    glEnableVertexAttribArray((GLuint)Renderer::VertexAttributeIndex::TextureUV);
    glVertexAttribPointer((GLuint)Renderer::VertexAttributeIndex::TextureUV, 2, GL_FLOAT, GL_FALSE, vertexSize, (GLvoid*)(uintptr_t)uvOffset);
    
    glBindVertexArray((GLuint)vaoCurrent);
    
    valid = true;
}

Mesh::~Mesh()
{
    if (vboVertices != 0)
        glDeleteBuffers(1, &vboVertices);
    
    if (vboIndices != 0)
        glDeleteBuffers(1, &vboIndices);
    
    if (vaoMesh != 0)
        glDeleteVertexArrays(1, &vaoMesh);
    
    delete[] this->data;
}
