#include "GamePlayState.hpp"

#include <optional>

#include "MenuState.hpp"
#include "StateMachine.hpp"

GamePlayState::GamePlayState(StateMachine &machine, sf::RenderWindow &window)
    : GameState(machine, window) { }

void GamePlayState::pause() { }

void GamePlayState::resume() { }

void GamePlayState::update(float) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      machine.quit();
    } else if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPressed->scancode == sf::Keyboard::Scancode::Escape) {
        machine.addState(machine.build<MenuState>(machine, window), true);
      }
    }
  }
}

void GamePlayState::draw() {
  window.clear(sf::Color(41, 137, 24));
  window.display();
}
