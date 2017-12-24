#pragma once

#include <types.hpp>
#include <Core.hpp>

#include <Shader.hpp>
#include <Mesh.hpp>

using namespace Anyon;

class Game : public Core::EventReceiver
{
public:
    Game();
    ~Game();
    
    void Initiaize() final;
    void Finalize() final;
    void Update(const double delta) final;
    
private:
    Shader *shader = nullptr;
    Mesh *mesh = nullptr;
    float angle = 0.f;
};

