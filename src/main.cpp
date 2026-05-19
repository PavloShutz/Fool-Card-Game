#include <SFML/Graphics.hpp>

#include "AI.hpp"
#include "Game.hpp"

int main() {
  std::vector<std::unique_ptr<Player> > players;
  players.push_back(std::make_unique<AI>("AI #1"));
  players.push_back(std::make_unique<AI>("AI #2"));
  players.push_back(std::make_unique<AI>("AI #3"));
  players.push_back(std::make_unique<AI>("AI #4"));
  players.push_back(std::make_unique<AI>("AI #5"));

  [[maybe_unused]] Game game{std::move(players)};
  game.run();
}
