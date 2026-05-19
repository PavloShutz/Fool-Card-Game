#ifndef GAMEPLAYSTATE_HPP
#define GAMEPLAYSTATE_HPP

#include "GameState.hpp"

class GamePlayState : public GameState {
public:
  GamePlayState(StateMachine &machine, sf::RenderWindow &window);
  ~GamePlayState() override = default;

  void pause() override;
  void resume() override;
  void update(float deltaTime) override;
  void draw() override;
};

#endif
