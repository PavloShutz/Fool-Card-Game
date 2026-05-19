#include "GamePlayState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

#include "StateMachine.hpp"

GamePlayState::GamePlayState(StateMachine& machine, sf::RenderWindow& window,
                             const bool replace)
    : GameState(machine, window, replace) {}

GamePlayState::~GamePlayState() = default;

void GamePlayState::pause() {}
void GamePlayState::resume() {}

void GamePlayState::update() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      machine.quit();
    } else if (const auto* keyPress = event->getIf<sf::Event::KeyPressed>()) {
      if (keyPress->code == sf::Keyboard::Key::Escape) {
        // Return to menu
        machine.lastState();
      }
    }
  }
}

void GamePlayState::draw() {
  window.clear(sf::Color::Green);
  // TODO: Draw game board and UI
  window.display();
}
