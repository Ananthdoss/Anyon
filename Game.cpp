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
    shader = new Shader("shader_unlit", {false}, Core()->ResourceManager());
    mesh = new Mesh("mesh_quad", Mesh::CommonShapes::Quad, Core()->ResourceManager());
    Core()->BeginTextInput();
}

void Game::Finalize()
{
    delete shader;
    delete mesh;
}

void Game::Update(const double delta)
{
    angle += delta * 10.f;
    
    Core()->Renderer()->Bind(shader);
    Matrix4 mv = Matrix4::MatrixTranslate({0.f, 0.f, -1.f}) * Matrix4::MatrixRotate(angle * toRad, {0.f, 0.f, 1.f});
    Matrix4 p = Matrix4::PerspectiveProjection((float)Core()->CurrentConfiguration().width / (float)Core()->CurrentConfiguration().height, 75.f * toRad, 0.1f, 100.f);
    shader->Set(shader->Index(Shader::defaultNames[(unsigned)Shader::defaultNameIndex::matrixMVP]), mv * p);
    Core()->Renderer()->Render(mesh);
}
