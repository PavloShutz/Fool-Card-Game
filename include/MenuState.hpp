//
// Created by User on 11.04.2026.
//

#ifndef FOOLCARDGAME_MENUSTATE_HPP
#define FOOLCARDGAME_MENUSTATE_HPP

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>
#include <vector>

#include "GameState.hpp"

namespace sf {
class RenderWindow;
}

struct Button {
  sf::RectangleShape shape;
  sf::Text           text;
  std::string        label;
  bool               isHovered;

  Button(const std::string& lbl, float x, float y, float width, float height,
         const sf::Font& font);
  
  bool isMouseOver(float mouseX, float mouseY) const;
  void setHovered(bool hovered);
  void draw(sf::RenderWindow& window) const;
};

class MenuState final : public GameState {
  sf::Texture backgroundTexture;
  sf::Sprite  background;
  sf::Font    font;
  
  std::vector<Button> buttons;
  float               mouseX;
  float               mouseY;

  void createButtons();

 public:
  MenuState(StateMachine& machine, sf::RenderWindow& window,
            bool replace = false);
  ~MenuState() override;

  void pause() override;
  void resume() override;
  void update() override;
  void draw() override;

 private:
  void handleMouseMove(float x, float y);
  void handleMouseClick(float x, float y);
};

#endif  // FOOLCARDGAME_MENUSTATE_HPP
