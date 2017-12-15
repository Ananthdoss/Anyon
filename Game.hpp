#pragma once

#include <types.hpp>
#include <Engine.hpp>

using namespace Anyon;

class Game : public Engine::Application
{
public:
    Game();
    ~Game();
    
    void Initiaize() final;
    void Finalize() final;
    void Update(const double delta) final;
};
