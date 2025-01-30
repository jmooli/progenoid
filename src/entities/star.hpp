#pragma once
#include <SFML/Graphics.hpp>

class Star {
public:
  Star(float x, float y, float speed, float size, sf::Color color);
  void update(float dt, float paddleOffset);
  void draw(sf::RenderWindow &window);
  bool isOffScreen() const;
  void reset(float newX, float newY);

private:
  sf::Vector2f position;
  float speed;
  float size;
  sf::CircleShape shape;
};
