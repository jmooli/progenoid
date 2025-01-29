#include "Button.hpp"
#include <SFML/Window/Mouse.hpp>
#include <iostream>

Button::Button(const sf::Vector2f &position, const sf::Vector2f &size,
               const std::string &text, sf::Font &font,
               std::function<void()> onClick)
    : buttonText(font), onClickCallback(onClick) {
  shape.setPosition(position);
  shape.setSize(size);
  shape.setFillColor(sf::Color::Blue);
  shape.setOutlineColor(sf::Color::White);
  shape.setOutlineThickness(2.f);

  buttonText.setFont(font);
  buttonText.setString(text);
  buttonText.setCharacterSize(24);
  buttonText.setFillColor(sf::Color::White);

  // Center the text within the button
  sf::FloatRect textRect = buttonText.getLocalBounds();
  buttonText.setOrigin(textRect.getCenter());
  buttonText.setPosition(
      {position.x + size.x / 2.f, position.y + size.y / 2.f});
}

bool Button::isMouseOver(const sf::RenderWindow &window) const {
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  sf::Vector2f mousePosF(static_cast<float>(mousePos.x),
                         static_cast<float>(mousePos.y));
  return shape.getGlobalBounds().contains(mousePosF);
}

void Button::handleEvent(const sf::Event &event,
                         const sf::RenderWindow &window) {
  if (const auto *mouseButtonPressed =
          event.getIf<sf::Event::MouseButtonPressed>()) {
    if (mouseButtonPressed->button == sf::Mouse::Button::Left) {
      std::cout << "the left button was pressed" << std::endl;
      std::cout << "mouse x: " << mouseButtonPressed->position.x << std::endl;
      std::cout << "mouse y: " << mouseButtonPressed->position.y << std::endl;

      if (isMouseOver(window)) {
        if (onClickCallback) {
          onClickCallback();
        }
      }

      if (isMouseOver(window)) {
        shape.setFillColor(sf::Color::Green);
      } else {
        shape.setFillColor(sf::Color::Blue);
      }
    }
  }
}

void Button::draw(sf::RenderWindow &window) {
  window.draw(shape);
  window.draw(buttonText);
}
