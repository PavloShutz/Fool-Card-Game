#pragma once

#include <string>
#include <vector>

#include "Card.hpp"

namespace Core {
class Player {
 public:
  Player();
  Player(std::string name);

 public:
  void         take(const Card& card);
  virtual void place(Table& dest) = 0;
  virtual bool beat(Table& table) = 0;

 private:
  std::string       m_name;
  std::vector<Card> m_cards;

  static unsigned cnt;
};
}  // namespace Core