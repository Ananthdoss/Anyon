#pragma once

#include <types.hpp>
#include <Core.hpp>

#include <Shader.hpp>
#include <Mesh.hpp>
#include <Texture.hpp>

using namespace Anyon;

class Game : public Core::EventReceiver
{
public:
    void PrepareConfiguration(Configuration &config) final;
    void Initiaize() final;
    void Finalize() final;
    void Update(const double delta) final;
    
private:
    Shader *shader = nullptr;
    Mesh *mesh = nullptr;
    Texture *texture = nullptr;
    float angle = 0.f;
};

