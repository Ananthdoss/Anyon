#include "Game.hpp"
#include <utils.hpp>
#include <iostream>

void Game::PrepareConfiguration(Configuration &config)
{
#ifdef ANYON_DEBUG
    std::cout << "Overriding with Debug configuraion" << std::endl;
    config.fsaa = false;
    config.vsync = false;
#endif
}

void Game::Initiaize()
{
    shader = Core()->MemoryManager()->New<class Shader, const std::string&, struct Shader::Properties, ResourceManager*>("shader_unlit", {true}, Core()->ResourceManager());
    mesh = Core()->MemoryManager()->New<class Mesh, const std::string&, Mesh::CommonShapes, ResourceManager*>("mesh_quad", Mesh::CommonShapes::Quad, Core()->ResourceManager());
    constexpr uint8_t data[] = {231, 120, 23, 56, 52, 49, 56, 52, 49, 231, 120, 23};
    texture = Core()->MemoryManager()->New<class Texture, const std::string&, const uint8_t*, unsigned, unsigned, Texture::PixelFormat, Texture::FilteringMode, bool, bool, ResourceManager*>("tex", data, 2, 2, Texture::PixelFormat::RGB8, Texture::FilteringMode::Linear, false, false, Core()->ResourceManager());
}

void Game::Finalize()
{
    Core()->MemoryManager()->Delete(shader);
    Core()->MemoryManager()->Delete(mesh);
    Core()->MemoryManager()->Delete(texture);
}

void Game::Update(const double delta)
{
    angle += delta * 10.f;
    
    Core()->Renderer()->Bind(shader);
    Core()->Renderer()->Bind(texture);
    
    Matrix4 mv = Matrix4::MatrixTranslate({0.f, 0.f, -1.f}) * Matrix4::MatrixRotate(angle * toRad, {0.f, 0.f, 1.f});
    Matrix4 p = Matrix4::PerspectiveProjection((float)Core()->CurrentConfiguration().width / (float)Core()->CurrentConfiguration().height, 75.f * toRad, 0.1f, 100.f);
    shader->Set(shader->Index(Shader::defaultNames[(unsigned)Shader::defaultNameIndex::matrixMVP]), mv * p);
    Core()->Renderer()->Render(mesh);
}
