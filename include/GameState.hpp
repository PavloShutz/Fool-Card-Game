//
// Created by User on 11.04.2026.
//

#ifndef FOOLCARDGAME_STATE_HPP
#define FOOLCARDGAME_STATE_HPP

#include <memory>

class StateMachine;

namespace sf {
class RenderWindow;
}

class GameState {
 protected:
  StateMachine&              machine;
  sf::RenderWindow&          window;
  bool                       replacing;
  std::unique_ptr<GameState> next;

 public:
  explicit GameState(StateMachine& machine, sf::RenderWindow& window,
                     bool replace = false);
  virtual ~GameState();

  virtual void pause()  = 0;
  virtual void resume() = 0;

  virtual void update() = 0;
  virtual void draw()   = 0;

  std::unique_ptr<GameState> getNextState();

  [[nodiscard]] bool isReplacing() const;
};

#endif  // FOOLCARDGAME_STATE_HPP
