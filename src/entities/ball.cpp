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

Ball::Ball(float x, float y, const sf::Texture &texture, float speedX,
           float speedY)
    : speedX(speedX), speedY(speedY) {

  this->sprite_ptr = std::make_unique<sf::Sprite>(texture);
  this->sprite_ptr->setPosition({x, y});
  this->sprite_ptr->setOrigin(
      {texture.getSize().x / 2.f, texture.getSize().y / 2.f});
}

void Ball::update(float dt, Paddle &paddle,
                  std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  // Predict next position
  sf::FloatRect nextPos = sprite_ptr->getGlobalBounds();
  float halfWidth = nextPos.size.x / 2;
  float nextLeft = nextPos.getCenter().x - halfWidth;
  float nextTop = nextPos.getCenter().y + halfWidth;

  nextLeft += speedX * dt * 2.5f; // Scaling factor to predict movement
  nextTop += speedY * dt * 2.5f;

  // There has to be better way for this
  nextPos = sf::FloatRect({nextLeft + halfWidth, nextTop + halfWidth},
                          sprite_ptr->getGlobalBounds().size);

  // 1️⃣ **Wall Collision** (Left, Right, Top)
  if (nextLeft < 0 || nextLeft + nextPos.size.x > 1920.f) {
    speedX = -speedX;
  }
  if (nextTop < 0) {
    speedY = -speedY;
  }

  // 2️⃣ **Paddle Collision**
  if (nextPos.findIntersection(paddle.getBounds()) != std::nullopt) {
    speedY = -std::abs(speedY); // Always bounce upwards
    RotateToCenter();
  }

  // 3️⃣ **Block Collision (Remove & Bounce)**
  for (auto it = gameObjects.begin(); it != gameObjects.end();) {
    auto *block = dynamic_cast<Block *>(it->get());
    if (block && nextPos.findIntersection(block->getBounds()) != std::nullopt) {
      speedY = -speedY;
      it = gameObjects.erase(it); // Remove block on hit
    } else {
      ++it;
    }
  }

  // **Move the Ball**
  sprite_ptr->move({speedX * dt * ballSpeed, speedY * dt * ballSpeed});
}
void Ball::draw(sf::RenderWindow &window) { window.draw(*sprite_ptr); }

sf::FloatRect Ball::getBounds() const { return sprite_ptr->getGlobalBounds(); }

void Ball::RotateToCenter() {
  float dx =
      std::abs(sprite_ptr->getPosition().x - (1920.f / 2)); // Window center
  float dy = std::abs(sprite_ptr->getPosition().y - (1080.f / 2));

  float rotation = (std::atan2(dy, dx)) * (180 / 3.14159f);
  sprite_ptr->rotate(sf::degrees(rotation)); // Slight rotation effect
}

void Ball::onCollision(GameObject &other) {
  if (hasCollidedThisFrame)
    return; // Prevent multiple collision resolutions

  hasCollidedThisFrame = true;

  sf::FloatRect ballRect = getBounds();
  sf::FloatRect otherRect = other.getBounds();
  sf::Vector2f ballCenter = ballRect.getCenter();
  sf::Vector2f otherCenter = otherRect.getCenter();

  sf::Vector2f ballHalfSize = {ballRect.size.x / 2.f, ballRect.size.y / 2.f};
  sf::Vector2f otherHalfSize = {otherRect.size.x / 2.f, otherRect.size.y / 2.f};

  float overlapX = (ballHalfSize.x + otherHalfSize.x) -
                   std::abs(ballCenter.x - otherCenter.x);
  float overlapY = (ballHalfSize.y + otherHalfSize.y) -
                   std::abs(ballCenter.y - otherCenter.y);

  if (overlapX > 0 && overlapY > 0) {
    // Determine collision side
    if (overlapX < overlapY) {
      // Horizontal collision
      speedX = -speedX;

      // Reposition ball
      float correctionX = (ballCenter.x < otherCenter.x) ? -overlapX : overlapX;
      sprite_ptr->move({correctionX, 0.f});
    } else {
      // Vertical collision
      speedY = -speedY;

      // Reposition ball
      float correctionY = (ballCenter.y < otherCenter.y) ? -overlapY : overlapY;
      sprite_ptr->move({0.f, correctionY});
    }
  }

  // Paddle Collision
  if (auto paddle = dynamic_cast<Paddle *>(&other)) {
    speedY = -std::abs(speedY); // Always move up after hitting the paddle

    // Adjust X velocity based on where the ball hit the paddle
    float hitPos =
        (ballCenter.x - otherCenter.x) / otherHalfSize.x; // Normalize [-1, 1]

    float maxDeflection = 300.f;
    speedX += hitPos * maxDeflection;

    // Reposition the ball just above the paddle
    sprite_ptr->setPosition({sprite_ptr->getPosition().x,
                             otherCenter.y - otherHalfSize.y - ballHalfSize.y});
  }

  if (std::abs(overlapX) < std::abs(overlapY)) {
    speedX = -speedX;
    sprite_ptr->move({overlapX, 0.f});
  } else {
    speedY = -speedY;
    sprite_ptr->move({0.f, overlapY});
  }
}

void Ball::attachToPaddle(const sf::Vector2f &paddlePosition) {
  attachedToPaddle = true;
  sprite_ptr->setPosition(
      {paddlePosition.x,
       paddlePosition.y - sprite_ptr->getGlobalBounds().size.y / 2});
}

void Ball::resetVelocity() {
  speedX = 0;
  speedY = 0;
}

bool Ball::isOutOfBounds(float height) {
  return sprite_ptr->getPosition().y > height;
}

void Ball::launch() {
  if (attachedToPaddle) {
    attachedToPaddle = false;
    speedX = 300.f;
    speedY = -300.f;
  }
}
