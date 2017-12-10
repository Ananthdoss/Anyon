#pragma once

#include <Engine.hpp>

using namespace AGE;

class Game : public Engine::Application
{
public:
    Game();
    ~Game();
    
    void Initiaize() final;
    void Free() final;
    void Update(const double delta) final;
};
