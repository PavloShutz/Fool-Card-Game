#pragma once

#include <initializer_list>
#include <memory>
#include <random>
#include <string>
#include <vector>

#include "Card.hpp"
#include "Player.hpp"

namespace Core {
constexpr std::size_t minNumberOfPlayers = 2, maxNumberOfPlayers = 6;

class Game {
 public:
  Game(std::initializer_list<std::shared_ptr<Player>> newPlayers);

  void run();

 private:
  void shuffleDeck();
  void dealCards();
  void determineTrump();

  void handleAttack();
  void handleDefend();
  void handleResult();
  void handleCleanup();

  bool checkWinCondition() const;

 private:
  Pile  deck;   // place to take cards from
  Table table;  // "battle area"
  Pile  heap;   // "used" cards will be stored here

  std::vector<std::shared_ptr<Player>> players;

  bool        running       = false;
  Suit        trump         = Suit::MAX_SUIT;
  std::size_t defenderIndex = 0;

  enum State { Attack, Defend, Result, Cleanup, MAX_STATE } state = MAX_STATE;

 private:  // facilities for randomness
  static std::random_device              rd;
  static std::mt19937_64                 g;
  static std::uniform_int_distribution<> dist;
};
}  // namespace Core