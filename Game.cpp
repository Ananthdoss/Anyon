#include "Game.hpp"
#include <utils.hpp>
#include <iostream>

Game::Game()
{
#ifndef DNDEBUG
    Core::config.vsync = false;
#endif
}

Game::~Game()
{

}

void Game::Initiaize()
{
    std::cout << "Ready to Rock?" << std::endl;
}

void Game::Finalize()
{
    std::cout << "Bye Bye!" << std::endl;
}

void Game::Update(const double delta)
{

}
