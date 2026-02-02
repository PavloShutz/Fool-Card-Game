#pragma once

#include "Player.hpp"

namespace Core {
class Human : virtual public Player {
 public:
  virtual void place(Table& dest) override;
  virtual bool beat(Table& table) override;
};
}  // namespace Core