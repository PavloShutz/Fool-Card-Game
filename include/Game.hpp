#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

#include "GameLap.hpp"
#include "Player.hpp"
#include "StateMachine.hpp"

class Game {
  std::unique_ptr<GameLap> gameLap;

  sf::RenderWindow window;
  StateMachine     machine;

 public:
  explicit Game(std::vector<std::unique_ptr<Player> > players);

  ~Game() = default;

  void run();
};

#endif