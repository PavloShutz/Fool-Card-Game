#ifndef STATEMACHINE_HPP
#define STATEMACHINE_HPP

#include <memory>
#include <utility>
#include <vector>

class GameState;

class StateMachine {
  std::vector<std::unique_ptr<GameState> > states;
  std::unique_ptr<GameState> newState;
  bool adding{false};
  bool replacing{false};
  bool removing{false};
  bool running{true};

public:
  StateMachine() = default;

  ~StateMachine() = default;

  void addState(std::unique_ptr<GameState> state, bool replace = true);
  void removeState();
  void processStateChanges();

  [[nodiscard]] bool isRunning() const {
    return running;
  }

  void quit() {
    running = false;
  }

  GameState &nextState() const;
  GameState &lastState() const;

  template<typename T, typename... Args>
  std::unique_ptr<GameState> build(Args &&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
  }
};

#endif
