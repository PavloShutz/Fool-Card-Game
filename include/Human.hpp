#pragma once

#include "Player.hpp"

namespace Core {
class Human : virtual public Player {
 public:
  virtual void place(Pile& source) override;
};
}  // namespace Core