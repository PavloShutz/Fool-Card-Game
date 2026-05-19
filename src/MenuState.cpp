#include "MenuState.hpp"

#include <filesystem>
#include <optional>

#include "GamePlayState.hpp"
#include "StateMachine.hpp"

Button::Button(const std::string &buttonLabel, float x, float y, float width, float height,
               const sf::Font &font)
    : text(font), label(buttonLabel) {
  shape.setSize({width, height});
  shape.setPosition({x, y});
  shape.setFillColor(sf::Color(70, 130, 180));
  shape.setOutlineThickness(2.f);
  shape.setOutlineColor(sf::Color::White);

  text.setString(label);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);

  const sf::FloatRect textBounds = text.getLocalBounds();
  text.setPosition({x + (width - textBounds.size.x) / 2.f,
                    y + (height - textBounds.size.y) / 2.f - textBounds.position.y});
}

bool Button::isMouseOver(float mouseX, float mouseY) const {
  return shape.getGlobalBounds().contains({mouseX, mouseY});
}

void Button::setHovered(bool hovered) {
  if (isHovered == hovered) {
    return;
  }

  isHovered = hovered;
  shape.setFillColor(isHovered ? sf::Color(100, 149, 237) : sf::Color(70, 130, 180));
}

void Button::draw(sf::RenderWindow &window) const {
  window.draw(shape);
  window.draw(text);
}

MenuState::MenuState(StateMachine &machine, sf::RenderWindow &window)
    : GameState(machine, window) {
  const std::filesystem::path fontPaths[] = {
      "assets/font.ttf",
      "assets/arial.ttf",
      "C:\\Windows\\Fonts\\arial.ttf",
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "/System/Library/Fonts/Arial.ttf"};

  for (const auto &path : fontPaths) {
    if (!std::filesystem::exists(path)) {
      continue;
    }

    try {
      font = sf::Font(path);
      hasFont = true;
      break;
    } catch (...) {
      hasFont = false;
    }
  }

  recreateButtons();
}

void MenuState::pause() { }

void MenuState::resume() { }

void MenuState::recreateButtons() {
  buttons.clear();
  if (!hasFont) {
    return;
  }

  constexpr float buttonWidth = 240.f;
  constexpr float buttonHeight = 64.f;
  constexpr float buttonGap = 20.f;

  const float windowWidth = static_cast<float>(window.getSize().x);
  const float windowHeight = static_cast<float>(window.getSize().y);
  const float totalHeight = buttonHeight * 2.f + buttonGap;
  const float startX = (windowWidth - buttonWidth) / 2.f;
  const float startY = (windowHeight - totalHeight) / 2.f;

  buttons.emplace_back("Start Game", startX, startY, buttonWidth, buttonHeight, font);
  buttons.emplace_back("Quit", startX, startY + buttonHeight + buttonGap, buttonWidth,
                       buttonHeight, font);
}

void MenuState::handleMouseMove(float mouseX, float mouseY) {
  for (auto &button : buttons) {
    button.setHovered(button.isMouseOver(mouseX, mouseY));
  }
}

void MenuState::handleMouseClick(float mouseX, float mouseY) {
  for (const auto &button : buttons) {
    if (!button.isMouseOver(mouseX, mouseY)) {
      continue;
    }

    if (button.label == "Start Game") {
      machine.addState(machine.build<GamePlayState>(machine, window), true);
    } else if (button.label == "Quit") {
      machine.quit();
    }
    return;
  }
}

void MenuState::update(float) {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      machine.quit();
    } else if (event->is<sf::Event::Resized>()) {
      recreateButtons();
    } else if (const auto *mouseMove = event->getIf<sf::Event::MouseMoved>()) {
      handleMouseMove(static_cast<float>(mouseMove->position.x),
                      static_cast<float>(mouseMove->position.y));
    } else if (const auto *mouseClick = event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouseClick->button == sf::Mouse::Button::Left) {
        handleMouseClick(static_cast<float>(mouseClick->position.x),
                         static_cast<float>(mouseClick->position.y));
      }
    }
  }
}

void MenuState::draw() {
  window.clear(sf::Color(32, 36, 44));

  for (const auto &button : buttons) {
    button.draw(window);
  }

  window.display();
}
