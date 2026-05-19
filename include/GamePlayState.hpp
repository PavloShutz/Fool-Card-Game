//
// Placeholder GamePlay state for future implementation
//

#ifndef FOOLCARDGAME_GAMEPLAYSTATE_HPP
#define FOOLCARDGAME_GAMEPLAYSTATE_HPP

#include "GameState.hpp"

namespace sf {
class RenderWindow;
}

class GamePlayState final : public GameState {
 public:
  GamePlayState(StateMachine& machine, sf::RenderWindow& window,
                bool replace = false);
  ~GamePlayState() override;

  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;
};

#endif  // FOOLCARDGAME_GAMEPLAYSTATE_HPP
