#include "Game.hpp"

Game::Game(std::vector<std::unique_ptr<Player> > players)
    : gameLap{std::make_unique<GameLap>(new StartState, std::move(players))} { }

void Game::init() const { gameLap->initContext(); }

void Game::run() const { gameLap->executeTurn(); }
