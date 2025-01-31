#pragma once

#include "game_object.hpp"
#include "paddle.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class Ball : public GameObject {
public:
  Ball(float x, float y, const sf::Texture &texture, float speedX,
       float speedY);

  void update(float dt, Paddle &paddle,
              std::vector<std::unique_ptr<GameObject>> &gameObjects) override;
  void draw(sf::RenderWindow &window) override;

  sf::FloatRect getBounds() const override;

  void onCollision(GameObject &other) override;

  void attachToPaddle(const sf::Vector2f &paddlePosition);
  void resetVelocity();
  void RotateToCenter();
  void launch();

  bool attachedToPaddle = true;
  bool isOutOfBounds(float height);

private:
  bool hasCollidedThisFrame = false;
  std::unique_ptr<sf::Sprite> sprite_ptr;
  float speedX;
  float speedY;
  float ballSpeed = 1.f;
};
