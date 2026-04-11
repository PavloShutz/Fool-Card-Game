#ifndef GAME_HPP
#define GAME_HPP

#include <memory>

#include "Player.hpp"
#include "GameLap.hpp"

class Game {
  std::unique_ptr<GameLap> gameLap;

public:
  explicit Game(std::vector<std::unique_ptr<Player> > players);

  ~Game() = default;

  void init() const;
  void run() const;
};

#endif