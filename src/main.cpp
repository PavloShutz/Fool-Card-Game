#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "AI.hpp"
#include "MenuState.hpp"
#include "StateMachine.hpp"

int main() {
  std::vector<std::unique_ptr<Player> > players;
  players.push_back(std::make_unique<AI>("AI #1"));
  players.push_back(std::make_unique<AI>("AI #2"));
  players.push_back(std::make_unique<AI>("AI #3"));
  players.push_back(std::make_unique<AI>("AI #4"));
  players.push_back(std::make_unique<AI>("AI #5"));

  [[maybe_unused]] const Game game{std::move(players)};

  auto window =
      sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Fool Card Game");
  window.setFramerateLimit(144u);

  StateMachine machine;
  machine.addState(machine.build<MenuState>(machine, window), true);

  sf::Clock clock;
  while (window.isOpen() && machine.isRunning()) {
    machine.processStateChanges();
    const float deltaTime = clock.restart().asSeconds();
    machine.nextState().update(deltaTime);
    machine.nextState().draw();
  }

  window.close();
}
