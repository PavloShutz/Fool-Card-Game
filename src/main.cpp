#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "AI.hpp"

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

  // Green felt-like background for the card table
  constexpr sf::Color BACKGROUND_COLOR(41, 137, 24);

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
