#pragma once

#include "game_object.hpp"
#include <SFML/Graphics/CircleShape.hpp>

class Ball : public GameObject {
public:
  Ball(const Ball &) = default;
  Ball(Ball &&) = default;
  Ball &operator=(const Ball &) = default;
  Ball &operator=(Ball &&) = default;
  Ball(float x, float y, float radius, float speedX, float speedY);

  void update(float dt) override;
  void draw(sf::RenderWindow &window) override;

  sf::FloatRect getBounds() const override;

  void onCollision(GameObject &other) override;

  void attachToPaddle(const sf::Vector2f &paddlePosition);
  void launch();

  bool attachedToPaddle = true;

private:
  bool hasCollidedThisFrame = false;
  sf::CircleShape shape;
  float speedX;
  float speedY;
};
