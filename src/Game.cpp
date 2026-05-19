#include "Game.hpp"

#include "MenuState.hpp"

Game::Game(std::vector<std::unique_ptr<Player> > players)
    : gameLap{std::make_unique<GameLap>(new StartState, std::move(players))} {
  gameLap->initContext();
}

void Game::run() {
  window.create(sf::VideoMode({1280u, 720u}), "Fool Card Game");
  window.setFramerateLimit(144u);
  // Green felt-like background for the card table
  // constexpr sf::Color BACKGROUND_COLOR(41, 137, 24);

  machine.run(StateMachine::build<MenuState>(machine, window, true));

  while (machine.isRunning()) {
    machine.nextState();
    machine.update();
    machine.draw();
  }
  // while (window.isOpen()) {
  //   while (const std::optional event = window.pollEvent()) {
  //     if (event->is<sf::Event::Closed>()) {
  //       window.close();
  //     }
  //   }
  //
  //   window.clear(BACKGROUND_COLOR);
  //
  //   window.display();
  // }
  // gameLap->executeTurn();
}
