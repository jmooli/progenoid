#include "block.hpp"
#include <SFML/Graphics/Color.hpp>

Block::Block(int type, float x, float y, float width, float height) {
  health = type;
  shape.setPosition({x, y});
  shape.setSize({width, height});
  updateColor();
}

void Block::update(float deltaTime) {}

void Block::draw(sf::RenderWindow &window) {
  if (!destroyed) {
    window.draw(shape);
  }
}

sf::FloatRect Block::getBounds() const { return shape.getGlobalBounds(); }

void Block::onCollision(GameObject &other) {
  health--;

  if (health <= 0) {
    destroyed = true;
    // add points etc
  }
  updateColor();
}

void Block::updateColor() {
  switch (health) {
  case 1:
    shape.setFillColor(sf::Color::Green);
    break;
  case 2:
    shape.setFillColor(sf::Color::Cyan);
    break;
  case 3:
    shape.setFillColor(sf::Color::Blue);
    break;
  case 4:
    shape.setFillColor(sf::Color::Magenta);
    break;
  case 5:
    shape.setFillColor(sf::Color::Red);
  }
}
