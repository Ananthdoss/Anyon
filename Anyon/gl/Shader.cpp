#include "Shader.hpp"
#include <cassert>
#include <iostream>

using namespace Anyon;

Shader::Shader(const std::string &name, struct Properties props, ResourceManager *resMan):
ResourceManager::Resource(name, resMan)
{
    std::string mvp(defaultNames[(unsigned)defaultNameIndex::matrixMVP]),
    dtex(defaultNames[(unsigned)defaultNameIndex::diffuseTexture]);
    
    std::string vs("#version 410 core\n");
    vs += "in vec4 vertexPos;\nuniform mat4 " + mvp + ";\n";
    if (props.diffuseTexture)
        vs += "in vec2 vertexUV;\nout vec2 varyingUV;\n";
    vs += "void main(){\n";
    if (props.diffuseTexture)
        vs += "varyingUV = vertexUV;\n";
    vs += "gl_Position = " + mvp + " * vertexPos;\n";
    vs += "}";
    
    GLuint vertShader = Compile(GL_VERTEX_SHADER, vs);
    
    std::string fs("#version 410 core\n");
    fs += "out vec4 fragColor;";
    if (props.diffuseTexture)
        fs += "in vec2 varyingUV;\nuniform sampler2D " + dtex + ";\n";
    fs += "void main(){\n";
    fs += "fragColor = vec4(1.0, 1.0, 1.0, 1.0);\n";
    if (props.diffuseTexture)
        fs += "fragColor *= texture(" + dtex + ", varyingUV);\n";
    fs += "}";
    
    GLuint fragShader = Compile(GL_FRAGMENT_SHADER, fs);
    
    assert(vertShader != 0 && fragShader != 0); // Failed to compile shaders source code!
    
    program = glCreateProgram();
    glAttachShader(program, vertShader);
    glAttachShader(program, fragShader);
    
    glBindAttribLocation(program, (GLuint)Renderer::VertexAttributeIndex::Position, "vertexPos");
    if (props.diffuseTexture)
        glBindAttribLocation(program, (GLuint)Renderer::VertexAttributeIndex::TextureUV , "vertexUV");
    
    valid = Link();
    assert(valid); // Failed to link shaders to program!
    
    if (vertShader)
    {
        glDetachShader(program, vertShader);
        glDeleteShader(vertShader);
    }
    
    if (fragShader)
    {
        glDetachShader(program, fragShader);
        glDeleteShader(fragShader);
    }
    
    Index(mvp);
    
    if (props.diffuseTexture)
        Index(dtex);
}

GLuint Shader::Compile(GLenum type, const std::string &source)
{
    GLuint shader = glCreateShader(type);
    const char *cstr = source.c_str();
    glShaderSource(shader, 1, &cstr, NULL);
    glCompileShader(shader);
    
#ifdef ANYON_DEBUG
    GLint length;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &length);
    if (length > 0)
    {
        GLchar *log = new GLchar[length];
        glGetShaderInfoLog(shader, length, &length, log);
        std::cout << "Shader compile log:" << std::endl << log << std::endl;
        delete[] log;
    }
#endif
    
    GLint status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    
    if (status == 0)
    {
        glDeleteShader(shader);
        return 0;
    }
    
    return shader;
}

bool Shader::Link()
{
    glLinkProgram(program);
    
#ifdef ANYON_DEBUG
    GLint length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    if (length > 0)
    {
        GLchar *log = new GLchar[length];
        glGetProgramInfoLog(program, length, &length, log);
        std::cout << "Program link log:" << std::endl << log << std::endl;
        delete[] log;
    }
#endif
    
    GLint status;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    return status == GL_TRUE;
}

bool Shader::Validate()
{
    glValidateProgram(program);
    
#ifdef ANYON_DEBUG
    GLint length;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
    if (length > 0)
    {
        GLchar *log = new GLchar[length];
        glGetProgramInfoLog(program, length, &length, log);
        std::cout << "Program validation log:" << std::endl << log << std::endl;
        delete[] log;
    }
#endif
    
    GLint status;
    glGetProgramiv(program, GL_VALIDATE_STATUS, &status);
    return status == GL_TRUE;
}

Shader::~Shader()
{
    if (program)
        glDeleteProgram(program);
}

struct Shader::Properties Shader::Properties() const
{
    return props;
}

Renderer::VertexAttributes Shader::CompatibleVertexAttributes() const
{
    return {props.diffuseTexture, false, false};
}

bool Shader::Valid() const
{
    return valid;
}

Renderer::StateObject::ObjectType Shader::Type() const
{
    return ObjectType::Shader;
}

GLuint Shader::Object() const
{
    return program;
}

int Shader::Index(const std::string &name)
{
    auto uf = uniforms.find(name);
    
    if (uf == uniforms.end())
    {
        int idx = (int)glGetUniformLocation(program, name.c_str());
        assert(idx != -1); // Uniform not found!
        uniforms.insert({name, idx});
        return idx;
    }
    else
        return uf->second;
}

void Shader::Set(int index, float f)
{
    glUniform1f((GLint)index, (GLfloat)f);
}

void Shader::Set(int index, int i)
{
    glUniform1i((GLint)index, (GLint)i);
}

void Shader::Set(int index, const Vector2 &v)
{
    glUniform2fv((GLint)index, 1, (GLfloat*)v.xy);
}

void Shader::Set(int index, const Vector3 &v)
{
    glUniform3fv((GLint)index, 1, (GLfloat*)v.xyz);
}

void Shader::Set(int index, const Color &c)
{
    glUniform4fv((GLint)index, 1, (GLfloat*)c.rgba);
}

void Shader::Set(int index, const Matrix4 &m)
{
    glUniformMatrix4fv(index, 1, GL_FALSE, m._1D);
}
