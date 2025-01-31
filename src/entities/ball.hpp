#pragma once

#include "game_object.hpp"
#include "paddle.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <memory>

class Ball : public GameObject {
public:
  Ball(int radius, const sf::Texture &texture, sf::Vector2f position,
       sf::Vector2u windowSize);

  void update(float dt, Paddle &paddle,
              std::vector<std::unique_ptr<GameObject>> &gameObjects) override;
  void draw(sf::RenderWindow &window) override;

  sf::FloatRect getBounds() const override;

  void onCollision(GameObject &other) override;

  void attachToPaddle(const sf::Vector2f &paddlePosition);
  void resetVelocity();
  void launch();

  bool checkCollision(sf::FloatRect obj1, float deltaTime);
  bool attachedToPaddle = true;
  bool isOutOfBounds(float height);

private:
  bool hasCollidedThisFrame = false;
  std::unique_ptr<sf::Sprite> sprite_ptr;
  sf::Vector2f ballVelocity;
  sf::Vector2u windowSize;
  float ballSpeed = 2.f;
  sf::FloatRect nextPos;
  void applyAngleDeflection(Paddle &paddle);
  sf::Vector2f startPos;
  sf::Vector2f startVelocity;
};
