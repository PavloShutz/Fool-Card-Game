#pragma once

#include "Player.hpp"

namespace Core {
class AI : virtual public Player {
  virtual void place(Pile& source) override;
};
}  // namespace Core