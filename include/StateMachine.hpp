//
// Created by User on 11.04.2026.
//

#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>
#include <stack>

#include "GameState.hpp"

namespace sf {
class RenderWindow;
}

class StateMachine {
  std::stack<std::unique_ptr<GameState>> states;
  bool                                   running{false};
  bool                                   resume{false};

 public:
  explicit StateMachine() = default;

  void run(std::unique_ptr<GameState> state);

  void nextState();
  void lastState();

  void update();
  void draw();

  [[nodiscard]] bool isRunning() const { return running; }
  void               quit();

  template <typename T>
  static std::unique_ptr<T> build(StateMachine&     machine,
                                  sf::RenderWindow& window,
                                  bool              replace = true);
};

template <typename T>
std::unique_ptr<T> StateMachine::build(StateMachine&     machine,
                                       sf::RenderWindow& window, bool replace) {
  return std::make_unique<T>(machine, window, replace);
}

#endif
