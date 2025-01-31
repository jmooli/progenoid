#include "wall.hpp"

Wall::Wall(float x, float y, float width, float height) {
  shape.setPosition({x, y});
  shape.setSize({width, height});
  shape.setFillColor(sf::Color::Blue);
}

void Wall::update(float dt, Paddle &paddle,
                  std::vector<std::unique_ptr<GameObject>> &gameObjects) {}

void Wall::draw(sf::RenderWindow &window) { window.draw(shape); }

sf::FloatRect Wall::getBounds() const { return shape.getGlobalBounds(); }

void Wall::onCollision(GameObject &other) {}
