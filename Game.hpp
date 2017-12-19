#pragma once

#include <types.hpp>
#include <Core.hpp>

using namespace Anyon;

class Game : public Core::Application
{
public:
    Game();
    ~Game();
    
    void Initiaize() final;
    void Finalize() final;
    void Update(const double delta) final;
};

