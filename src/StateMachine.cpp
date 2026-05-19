#include "StateMachine.hpp"

#include <stdexcept>

#include "GameState.hpp"

void StateMachine::addState(std::unique_ptr<GameState> state, bool replace) {
  newState = std::move(state);
  adding = true;
  replacing = replace;
}

void StateMachine::removeState() {
  removing = true;
}

void StateMachine::processStateChanges() {
  if (removing && !states.empty()) {
    states.pop_back();
    if (states.empty()) {
      running = false;
    } else {
      states.back()->resume();
    }
    removing = false;
  }

  if (adding && newState) {
    if (!states.empty()) {
      if (replacing) {
        states.pop_back();
      } else {
        states.back()->pause();
      }
    }

    states.push_back(std::move(newState));
    states.back()->resume();
    adding = false;
  }
}

GameState &StateMachine::nextState() const {
  if (states.empty()) {
    throw std::runtime_error("StateMachine::nextState called with no active states");
  }

  return *states.back();
}

GameState &StateMachine::lastState() const {
  if (states.empty()) {
    throw std::runtime_error("StateMachine::lastState called with no active states");
  }

  if (states.size() < 2) {
    return *states.back();
  }

  return *states[states.size() - 2];
}
