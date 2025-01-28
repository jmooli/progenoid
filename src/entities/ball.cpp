#include "ball.hpp"
#include "paddle.hpp"
#include <cmath>
#include <iostream>

Ball::Ball(float x, float y, float radius, float speedX, float speedY)
    : speedX(speedX), speedY(speedY), attachedToPaddle(true) {
  shape.setPosition({x, y});
  shape.setRadius(radius);
  shape.setOrigin({radius, radius});
  shape.setFillColor(sf::Color::White);
}

void Ball::update(float dt) {
  // reset the collision flag
  hasCollidedThisFrame = false;
  // TODO:get rid of these hardcoded sizes
  float screenWidth = 1920.f;
  float screenHeight = 1920.f;

  if (attachedToPaddle) {
    return;
  }

  shape.move({speedX * dt, speedY * dt});

  float radius = shape.getRadius();
  sf::Vector2f pos = shape.getPosition();

  if (pos.x - radius < 0.f) {
    pos.x = radius;
    speedX = -speedX;
  } else if (pos.x + radius > screenWidth) {
    pos.x = screenWidth - radius;
    speedX = -speedX;
  }
  if (pos.y - radius < 0.f) {
    pos.y = radius;
    speedY = -speedY;
  }
  shape.setPosition(pos);
}

void Ball::draw(sf::RenderWindow &window) {
  window.draw(shape);

  // Draw bounding box for debugging
  sf::RectangleShape bbox;
  bbox.setPosition(shape.getGlobalBounds().position);
  bbox.setSize(shape.getGlobalBounds().size);
  bbox.setFillColor(sf::Color::Transparent);
  bbox.setOutlineColor(sf::Color::Red);
  bbox.setOutlineThickness(1.f);
  window.draw(bbox);
}

sf::FloatRect Ball::getBounds() const { return shape.getGlobalBounds(); }

void Ball::onCollision(GameObject &other) {
  if (hasCollidedThisFrame)
    return; // Prevent multiple collision resolutions

  hasCollidedThisFrame = true;

  // Log collision for debugging
  std::cout << "Ball onCollision with " << typeid(other).name() << std::endl;

  // Get bounding boxes
  sf::FloatRect ballRect = shape.getGlobalBounds();
  sf::FloatRect otherRect = other.getBounds();

  float ballLeft = ballRect.position.x;
  float ballTop = ballRect.position.y;
  float ballWidth = ballRect.size.x;
  float ballHeight = ballRect.size.y;

  float otherLeft = otherRect.position.x;
  float otherTop = otherRect.position.y;
  float otherWidth = otherRect.size.x;
  float otherHeight = otherRect.size.y;

  float ballRight = ballLeft + ballWidth;
  float ballBottom = ballTop + ballHeight;

  float otherRight = otherLeft + otherWidth;
  float otherBottom = otherTop + otherHeight;

  float overlapLeft = ballRight - otherLeft;
  float overlapRight = otherRight - ballLeft;
  float overlapTop = ballBottom - otherTop;
  float overlapBottom = otherBottom - ballTop;

  bool ballFromLeft = (std::abs(overlapLeft) < std::abs(overlapRight));
  bool ballFromTop = (std::abs(overlapTop) < std::abs(overlapBottom));

  float minOverlapX = ballFromLeft ? overlapLeft : overlapRight;
  float minOverlapY = ballFromTop ? overlapTop : overlapBottom;

  if (auto paddle = dynamic_cast<Paddle *>(&other)) {
    // Specific handling for paddle collision

    // Reflect the Y velocity
    speedY = -std::abs(speedY); // Ensure the ball always moves upwards after
                                // hitting the paddle

    // Adjust X velocity based on hit position
    float paddleCenter = otherRect.position.x + otherRect.size.x / 2.f;
    float ballCenter = ballRect.position.x + ballRect.size.x / 2.f;
    float hitPos = (ballCenter - paddleCenter) /
                   (otherRect.size.x / 2.f); // Normalize between -1 and 1

    float maxDeflection = 300.f; // Adjust as needed
    speedX += hitPos * maxDeflection;

    // Reposition the ball to be just above the paddle
    float newY =
        otherTop - shape.getRadius(); // Position center.y = paddleTop - radius
    shape.setPosition({shape.getPosition().x, newY});

    std::cout << "Ball position after collision with Paddle: ("
              << shape.getPosition().x << ", " << shape.getPosition().y
              << ")\n";
  } else {
    // Handle collisions with other objects (blocks, etc.)
    if (std::abs(minOverlapX) < std::abs(minOverlapY)) {
      // Horizontal collision → flip X velocity
      speedX = -speedX;
      // Move the ball out of collision on X‐axis
      shape.move({minOverlapX, 0.f});
    } else {
      // Vertical collision → flip Y velocity
      speedY = -speedY;
      // Move the ball out of collision on Y‐axis
      shape.move({0.f, minOverlapY});
    }
  }

  // Log velocity after collision
  std::cout << "Ball velocity after collision: (" << speedX << ", " << speedY
            << ")" << std::endl;
}

void Ball::attachToPaddle(const sf::Vector2f &paddlePosition) {
  attachedToPaddle = true;
  shape.setPosition({paddlePosition.x, paddlePosition.y - shape.getRadius()});
}

void Ball::launch() {
  if (attachedToPaddle) {
    attachedToPaddle = false;

    speedX = 300.f;
    speedY = -300.f;
  }
}
