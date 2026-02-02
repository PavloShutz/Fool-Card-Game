#pragma once

#include "Player.hpp"

namespace Core {
class AI : virtual public Player {
  virtual bool place(Table& dest) override;
  virtual bool beat(Table& table) override;
};
}  // namespace Core