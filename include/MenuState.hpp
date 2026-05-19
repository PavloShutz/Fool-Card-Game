#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "GameState.hpp"

struct Button {
  sf::RectangleShape shape;
  sf::Text text;
  std::string label;
  bool isHovered{false};

  Button(const std::string &label, float x, float y, float width, float height,
         const sf::Font &font);
  bool isMouseOver(float mouseX, float mouseY) const;
  void setHovered(bool hovered);
  void draw(sf::RenderWindow &window) const;
};

class MenuState : public GameState {
  std::vector<Button> buttons;
  sf::Font font;
  bool hasFont{false};

public:
  MenuState(StateMachine &machine, sf::RenderWindow &window);
  ~MenuState() override = default;

  void pause() override;
  void resume() override;
  void update(float deltaTime) override;
  void draw() override;

private:
  void recreateButtons();
  void handleMouseMove(float mouseX, float mouseY);
  void handleMouseClick(float mouseX, float mouseY);
};

#endif
