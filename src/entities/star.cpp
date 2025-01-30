#include "star.hpp"

Star::Star(float x, float y, float speed, float size, sf::Color color)
    : position(x, y), speed(speed), size(size) {
  shape.setPosition(position);
  shape.setRadius(size);
  shape.setFillColor(color);
}

void Star::update(float dt, float paddleOffset) {
  position.y += speed * dt;

  position.x -= paddleOffset * (speed * 0.01f);

  shape.setPosition(position);
}

void Star::draw(sf::RenderWindow &window) { window.draw(shape); }

bool Star::isOffScreen() const { return position.y > 1080; }

void Star::reset(float newX, float newY) {
  position = {newX, newY};
  shape.setPosition(position);
}
