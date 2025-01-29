#pragma once

#include "game_object.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class Ball : public GameObject {
public:
  Ball(float x, float y, float radius, float speedX, float speedY);

  void update(float dt) override;
  void draw(sf::RenderWindow &window) override;

  sf::FloatRect getBounds() const override;

  void onCollision(GameObject &other) override;

  void attachToPaddle(const sf::Vector2f &paddlePosition);
  void reattachToPaddle(const sf::Vector2f &paddlePosition);
  void resetVelocity();

  void launch();

  bool attachedToPaddle = true;
  bool isOutOfBounds(float height);

private:
  bool hasCollidedThisFrame = false;
  sf::CircleShape shape;
  float speedX;
  float speedY;
};
