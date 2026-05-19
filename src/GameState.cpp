#include "GameState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

#include "StateMachine.hpp"

GameState::GameState(StateMachine& machine, sf::RenderWindow& window,
                     const bool replace)
    : machine(machine), window(window), replacing(replace) { }

GameState::~GameState() = default;

std::unique_ptr<GameState> GameState::getNextState() { return std::move(next); }
bool                       GameState::isReplacing() const { return replacing; }