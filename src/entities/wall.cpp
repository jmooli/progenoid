#include "wall.hpp"

Wall::Wall(float x, float y, float width, float height) {
  shape.setPosition({x, y});
  shape.setSize({width, height});
  shape.setFillColor(sf::Color::Blue);
}

void Wall::update(float dt) {}

void Wall::draw(sf::RenderWindow &window) { window.draw(shape); }

sf::FloatRect Wall::getBounds() const { return shape.getGlobalBounds(); }

void Wall::onCollision(GameObject &other) {}
