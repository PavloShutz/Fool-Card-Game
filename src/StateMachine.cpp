//
// Created by User on 11.04.2026.
//

#include "StateMachine.hpp"

#include <SFML/Graphics/RenderWindow.hpp>

void StateMachine::run(std::unique_ptr<GameState> state) {
  running = true;
  states.push(std::move(state));
}

void StateMachine::nextState() {
  if (resume) {
    // clean up the current state
    if (!states.empty()) {
      states.pop();
    }

    // resume previous state
    if (!states.empty()) {
      states.top()->resume();
    }

    resume = false;
  }

  if (!states.empty()) {
    if (auto temp = states.top()->getNextState()) {
      if (temp->isReplacing()) {  // replace the running state
        states.pop();
      } else {  // pause the running state
        states.top()->pause();
      }
      states.push(std::move(temp));
    }
  }
}

void StateMachine::lastState() { resume = true; }
void StateMachine::update() { states.top()->update(); }
void StateMachine::draw() { states.top()->draw(); }
void StateMachine::quit() { running = false; }