#include "ball.hpp"
#include "block.hpp"
#include "paddle.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <memory>
#include <optional>

Ball::Ball(int radius, const sf::Texture &texture, sf::Vector2f position,
           sf::Vector2u windowSize) {
  sprite_ptr = std::make_unique<sf::Sprite>(texture);
  sprite_ptr->setPosition(position);
  sprite_ptr->setOrigin({texture.getSize().x / 2.f, texture.getSize().y / 2.f});
  this->ballSpeed = 400.f;
  this->windowSize = windowSize;
  this->startPos = position;
  this->ballVelocity = {0.f, 0.f};
  this->startVelocity = ballVelocity;
}

void Ball::update(float dt, Paddle &paddle,
                  std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  // Normalize velocity and apply speed
  float length = std::sqrt(ballVelocity.x * ballVelocity.x +
                           ballVelocity.y * ballVelocity.y);
  if (length != 0) {
    ballVelocity = (ballVelocity / length) * ballSpeed;
  }

  // **Divide movement into smaller steps to prevent tunneling**
  const int steps = 10; // Number of sub-steps per frame
  float subDt = dt / steps;

  for (int i = 0; i < steps; i++) {
    // **Predict next position**
    sf::FloatRect ballBounds = sprite_ptr->getGlobalBounds();
    sf::Vector2f nextCenter = ballBounds.getCenter() + (ballVelocity * subDt);

    // **Convert center-based position to bounding box**
    sf::FloatRect nextPos({nextCenter.x - (ballBounds.size.x / 2),
                           nextCenter.y - (ballBounds.size.y / 2)},
                          ballBounds.size);

    // **Boundary collisions**
    if (nextPos.getCenter().x - (nextPos.size.x / 2) < 0) { // Left wall
      ballVelocity.x *= -1;
    } else if (nextPos.getCenter().x + (nextPos.size.x / 2) >
               windowSize.x) { // Right wall
      ballVelocity.x *= -1;
    } else if (nextPos.getCenter().y - (nextPos.size.y / 2) < 0) { // Top wall
      ballVelocity.y *= -1;
    }

    // **Paddle Collision**
    if (checkCollision(paddle.getBounds(), subDt)) {
      ballVelocity.y = -std::abs(ballVelocity.y);
      applyAngleDeflection(paddle);
    }

    // **Block Collisions**
    for (auto &obj : gameObjects) {
      if (obj.get() != this && checkCollision(obj->getBounds(), subDt)) {
        onCollision(*obj);
      }
    }

    // **Move the ball AFTER checking for collisions**
    sprite_ptr->setPosition(nextCenter);
  }
}

void Ball::onCollision(GameObject &other) {
  auto block = dynamic_cast<Block *>(&other);
  if (!block)
    return;

  sf::FloatRect ballBounds = sprite_ptr->getGlobalBounds();
  sf::FloatRect blockBounds = block->getBounds();

  // **Calculate overlap distances**
  float overlapX = blockBounds.getCenter().x - ballBounds.getCenter().x;
  float overlapY = blockBounds.getCenter().y - ballBounds.getCenter().y;

  float absOverlapX = std::abs(overlapX);
  float absOverlapY = std::abs(overlapY);

  if (absOverlapX > absOverlapY) {
    // **Horizontal collision → Flip X velocity**
    ballVelocity.x *= -1;

    // **Push ball out of block on X-axis**
    if (overlapX > 0) {
      sprite_ptr->setPosition({blockBounds.getCenter().x -
                                   blockBounds.size.x / 2 -
                                   ballBounds.size.x / 2,
                               sprite_ptr->getPosition().y});
    } else {
      sprite_ptr->setPosition({blockBounds.getCenter().x +
                                   blockBounds.size.x / 2 +
                                   ballBounds.size.x / 2,
                               sprite_ptr->getPosition().y});
    }
  } else {
    // **Vertical collision → Flip Y velocity**
    ballVelocity.y *= -1;

    // **Push ball out of block on Y-axis**
    if (overlapY > 0) {
      sprite_ptr->setPosition(
          {sprite_ptr->getPosition().x, blockBounds.getCenter().y -
                                            blockBounds.size.y / 2 -
                                            ballBounds.size.y / 2});
    } else {
      sprite_ptr->setPosition(
          {sprite_ptr->getPosition().x, blockBounds.getCenter().y +
                                            blockBounds.size.y / 2 +
                                            ballBounds.size.y / 2});
    }
  }
}

void Ball::applyAngleDeflection(Paddle &paddle) {
  float paddleCenterX = paddle.getBounds().getCenter().x;
  float ballCenterX = sprite_ptr->getGlobalBounds().getCenter().x;
  float hitOffset =
      (ballCenterX - paddleCenterX) / (paddle.getBounds().size.x / 2.f);

  // Apply slight horizontal deflection
  float maxDeflection = 500.f;
  ballVelocity.x += hitOffset * maxDeflection;

  // Normalize to maintain speed
  float length = std::sqrt(ballVelocity.x * ballVelocity.x +
                           ballVelocity.y * ballVelocity.y);
  if (length != 0) {
    ballVelocity = (ballVelocity / length) * ballSpeed;
  }
}

bool Ball::checkCollision(sf::FloatRect obj1, float deltaTime) {
  sf::FloatRect nextPos = sprite_ptr->getGlobalBounds();

  // Predict next position based on velocity
  sf::Vector2f nextCenter = nextPos.getCenter() + (ballVelocity * deltaTime);

  // Convert center-based position to rectangle position
  sf::FloatRect predictedBounds({nextCenter.x - (nextPos.size.x / 2),
                                 nextCenter.y - (nextPos.size.y / 2)},
                                nextPos.size);

  // Check for intersection
  return obj1.findIntersection(predictedBounds) != std::nullopt;
}

void Ball::draw(sf::RenderWindow &window) { window.draw(*sprite_ptr); }

sf::FloatRect Ball::getBounds() const { return sprite_ptr->getGlobalBounds(); }

void Ball::attachToPaddle(const sf::Vector2f &paddlePosition) {
  attachedToPaddle = true;
  sprite_ptr->setPosition(
      {paddlePosition.x,
       paddlePosition.y - sprite_ptr->getGlobalBounds().size.y / 2});
}

void Ball::resetVelocity() { this->ballVelocity = startVelocity; }

bool Ball::isOutOfBounds(float height) {
  if (sprite_ptr->getPosition().y > height) {
    // Reset ball position and velocity
    sprite_ptr->setPosition(startPos);
    resetVelocity();
    attachedToPaddle = true;
    return true;
  }
  return false;
}

void Ball::launch() {
  if (attachedToPaddle) {
    attachedToPaddle = false;
    // Set initial velocity (adjust as needed)
    ballVelocity = {0.5f, -1.f}; // Example direction
    // Normalize velocity
    float length = std::sqrt(ballVelocity.x * ballVelocity.x +
                             ballVelocity.y * ballVelocity.y);
    ballVelocity = (ballVelocity / length) * ballSpeed;
  }
}
