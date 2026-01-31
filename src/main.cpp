#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main() {
  /*Core::Game game{
      std::make_shared<Core::Player>(),
      std::make_shared<Core::Player>(),
      std::make_shared<Core::Player>(),
      std::make_shared<Core::Player>(),
      std::make_shared<Core::Player>(),
  };*/

  auto window =
      sf::RenderWindow(sf::VideoMode({1280u, 720u}), "Fool Card Game");
  window.setFramerateLimit(144u);

  // Green felt-like background for the card table
  const sf::Color BACKGROUND_COLOR(41, 137, 24);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear(BACKGROUND_COLOR);

    window.display();
  }
}
