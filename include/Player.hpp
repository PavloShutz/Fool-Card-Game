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
  virtual void place(Pile& dest) = 0;
  
 private:
  std::string       m_name;
  std::vector<Card> m_cards;

  static unsigned cnt;
};
}  // namespace Core