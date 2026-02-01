#pragma once

#include "Player.hpp"

namespace Core {
class AI : virtual public Player {
  virtual void place(Table& dest) override;
};
}  // namespace Core