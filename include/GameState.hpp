#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics/RenderWindow.hpp>

class StateMachine;

class GameState {
protected:
  StateMachine &machine;
  sf::RenderWindow &window;

public:
  GameState(StateMachine &machine, sf::RenderWindow &window)
      : machine(machine), window(window) { }

  virtual ~GameState() = default;

  virtual void pause() = 0;
  virtual void resume() = 0;
  virtual void update(float deltaTime) = 0;
  virtual void draw() = 0;
};

#endif
