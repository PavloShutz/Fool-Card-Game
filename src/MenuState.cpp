#include "MenuState.hpp"

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <filesystem>
#include <exception>

#include "StateMachine.hpp"
#include "GamePlayState.hpp"

// Button Implementation
Button::Button(const std::string& lbl, float x, float y, float width,
               float height, const sf::Font& font)
    : label(lbl), isHovered(false), text(font) {
  shape.setPosition({x, y});
  shape.setSize({width, height});
  shape.setFillColor(sf::Color::Blue);
  shape.setOutlineThickness(2.f);
  shape.setOutlineColor(sf::Color::White);

  text.setString(label);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);

  // Center text in button
  auto bounds = text.getLocalBounds();
  text.setPosition({
      x + (width - bounds.size.x) / 2.f,
      y + (height - bounds.size.y) / 2.f - 5.f});
}

bool Button::isMouseOver(float mouseX, float mouseY) const {
  return shape.getGlobalBounds().contains({mouseX, mouseY});
}

void Button::setHovered(bool hovered) {
  isHovered = hovered;
  if (isHovered) {
    shape.setFillColor(sf::Color::Cyan);
  } else {
    shape.setFillColor(sf::Color::Blue);
  }
}

void Button::draw(sf::RenderWindow& window) const {
  window.draw(shape);
  window.draw(text);
}

// MenuState Implementation
MenuState::MenuState(StateMachine& machine, sf::RenderWindow& window,
                     const bool replace)
    : GameState(machine, window, replace),
      backgroundTexture("assets/Menu.png"),
      background(backgroundTexture),
      mouseX(0.f),
      mouseY(0.f) {
  background.setPosition({0, 0});

  // Try to load font - use system paths as fallbacks
  const std::filesystem::path fontPaths[] = {
      "assets/font.ttf",
      "C:\\Windows\\Fonts\\arial.ttf",
      "C:\\Windows\\Fonts\\Arial.ttf",
      "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
      "/System/Library/Fonts/Arial.ttf"};
  
  for (const auto& path : fontPaths) {
    if (std::filesystem::exists(path)) {
      try {
        font = sf::Font(path);
        break;
      } catch (const std::exception& e) {
        // Font loading failed, try next path
        continue;
      }
    }
  }

  createButtons();
}

MenuState::~MenuState() = default;

void MenuState::createButtons() {
  const float buttonWidth = 200.f;
  const float buttonHeight = 60.f;
  const float windowWidth = window.getSize().x;
  const float windowHeight = window.getSize().y;

  // Center buttons horizontally, position vertically
  float startX = (windowWidth - buttonWidth) / 2.f;
  float startGameY = windowHeight / 2.f - 100.f;
  float quitY = windowHeight / 2.f + 50.f;

  buttons.emplace_back("Start Game", startX, startGameY, buttonWidth,
                       buttonHeight, font);
  buttons.emplace_back("Quit", startX, quitY, buttonWidth, buttonHeight, font);
}

void MenuState::pause() {}
void MenuState::resume() {}

void MenuState::handleMouseMove(float x, float y) {
  mouseX = x;
  mouseY = y;

  for (auto& button : buttons) {
    button.setHovered(button.isMouseOver(x, y));
  }
}

void MenuState::handleMouseClick(float x, float y) {
  if (buttons.size() < 2) return;

  if (buttons[0].isMouseOver(x, y)) {
    // Start Game button clicked
    next = StateMachine::build<GamePlayState>(machine, window, true);
  } else if (buttons[1].isMouseOver(x, y)) {
    // Quit button clicked
    machine.quit();
  }
}

void MenuState::update() {
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      machine.quit();
    } else if (const auto* mouseMove = event->getIf<sf::Event::MouseMoved>()) {
      handleMouseMove(static_cast<float>(mouseMove->position.x),
                      static_cast<float>(mouseMove->position.y));
    } else if (const auto* mouseClick =
                   event->getIf<sf::Event::MouseButtonPressed>()) {
      if (mouseClick->button == sf::Mouse::Button::Left) {
        handleMouseClick(static_cast<float>(mouseClick->position.x),
                         static_cast<float>(mouseClick->position.y));
      }
    }
  }
}

void MenuState::draw() {
  window.clear();
  window.draw(background);

  for (auto& button : buttons) {
    button.draw(window);
  }

  window.display();
}