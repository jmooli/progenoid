#include "ball.hpp"
#include "block.hpp"
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <optional>

Ball::Ball(int radius, const sf::Texture &texture, sf::Vector2f position,
           sf::Vector2u windowSize)
    : windowSize(windowSize), startPos(position) {
  sprite_ptr = std::make_unique<sf::Sprite>(texture);
  sprite_ptr->setPosition(position);
  sprite_ptr->setOrigin({texture.getSize().x / 2.f, texture.getSize().y / 2.f});

  // Initially, the ball is stationary until launched.
  ballVelocity = {0.f, 0.f};
  startVelocity = ballVelocity;
}

void Ball::update(float dt, Paddle &paddle,
                  std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  // Normalize velocity and apply constant speed
  float length = std::sqrt(ballVelocity.x * ballVelocity.x +
                           ballVelocity.y * ballVelocity.y);
  if (length != 0.f) {
    ballVelocity = (ballVelocity / length) * ballSpeed;
  }

  // Increase collision precision by substepping
  const int steps = 20;
  float subDt = dt / steps;
  for (int i = 0; i < steps; ++i) {
    sf::FloatRect currentBounds = sprite_ptr->getGlobalBounds();
    sf::Vector2f currentCenter = currentBounds.getCenter();
    sf::Vector2f nextCenter = currentCenter + ballVelocity * subDt;

    // Handle collisions with the window boundaries
    handleWallCollision(nextCenter, currentBounds);

    // Predict the next bounds based on nextCenter
    sf::FloatRect nextBounds({nextCenter.x - currentBounds.size.x / 2.f,
                              nextCenter.y - currentBounds.size.y / 2.f},
                             {currentBounds.size.x, currentBounds.size.y});

    bool collisionOccurred = false;
    // Check for paddle collision first
    if (handlePaddleCollision(paddle, subDt, nextCenter, currentBounds)) {
      collisionOccurred = true;
    }
    // Then check for block collisions (only one collision per substep)
    else if (handleBlockCollisions(gameObjects, subDt, nextCenter,
                                   currentBounds)) {
      collisionOccurred = true;
    }

    // Update the sprite position (collision handlers may have adjusted
    // ballVelocity)
    sprite_ptr->setPosition(nextCenter);
  }
}

void Ball::handleWallCollision(sf::Vector2f &nextCenter,
                               const sf::FloatRect &bounds) {
  float halfWidth = bounds.size.x / 2.f;
  float halfHeight = bounds.size.y / 2.f;

  // Left wall
  if (nextCenter.x - halfWidth < 0.f) {
    nextCenter.x = halfWidth;
    ballVelocity.x = std::abs(ballVelocity.x);
  }
  // Right wall
  else if (nextCenter.x + halfWidth > windowSize.x) {
    nextCenter.x = windowSize.x - halfWidth;
    ballVelocity.x = -std::abs(ballVelocity.x);
  }

  // Top wall
  if (nextCenter.y - halfHeight < 0.f) {
    nextCenter.y = halfHeight;
    ballVelocity.y = std::abs(ballVelocity.y);
  }
}

bool Ball::handlePaddleCollision(Paddle &paddle, float subDt,
                                 sf::Vector2f &nextCenter,
                                 const sf::FloatRect &currentBounds) {
  if (checkCollision(paddle.getBounds(), subDt)) {
    // Invert the vertical component of the velocity (ensuring upward movement)
    ballVelocity.y = -std::abs(ballVelocity.y);
    // Apply angle deflection based on where the ball hit the paddle
    applyAngleDeflection(paddle);

    // Adjust nextCenter to avoid sinking into the paddle (optional additional
    // adjustment)
    nextCenter.y = paddle.getBounds().getCenter().y -
                   paddle.getBounds().size.y / 2.f -
                   currentBounds.size.y / 2.f - 1.f;
    return true;
  }
  return false;
}

bool Ball::handleBlockCollisions(
    std::vector<std::unique_ptr<GameObject>> &gameObjects, float subDt,
    sf::Vector2f &nextCenter, const sf::FloatRect &currentBounds) {
  sf::FloatRect currentBoundsCopy = currentBounds;
  // Predict the next bounds
  sf::FloatRect nextBounds({nextCenter.x - currentBounds.size.x / 2.f,
                            nextCenter.y - currentBounds.size.y / 2.f},
                           {currentBounds.size.x, currentBounds.size.y});

  for (auto &obj : gameObjects) {
    // Skip self and non-block objects
    if (obj.get() == this)
      continue;

    auto block = dynamic_cast<Block *>(obj.get());
    if (block && checkCollision(block->getBounds(), subDt)) {
      resolveBlockCollision(*block, currentBoundsCopy, nextBounds);
      return true;
    }
  }
  return false;
}

bool Ball::checkCollision(const sf::FloatRect &otherBounds, float deltaTime) {
  // Predict next bounds based on current velocity and deltaTime
  sf::FloatRect currentBounds = sprite_ptr->getGlobalBounds();
  sf::Vector2f currentCenter = currentBounds.getCenter();
  sf::Vector2f predictedCenter = currentCenter + ballVelocity * deltaTime;

  sf::FloatRect predictedBounds(
      {predictedCenter.x - currentBounds.size.x / 2.f,
       predictedCenter.y - currentBounds.size.y / 2.f},
      {currentBounds.size.x, currentBounds.size.y});

  // Use findIntersection() which returns a std::optional<sf::FloatRect>
  return predictedBounds.findIntersection(otherBounds) != std::nullopt;
}

void Ball::applyAngleDeflection(Paddle &paddle) {
  // Calculate the offset between the ball and paddle centers
  float paddleCenterX = paddle.getBounds().getCenter().x;
  float ballCenterX = sprite_ptr->getGlobalBounds().getCenter().x;
  float hitOffset =
      (ballCenterX - paddleCenterX) / (paddle.getBounds().size.x / 2.f);

  // Define the minimum angle (20°) in radians
  const float MIN_ANGLE = 20.f * M_PI / 180.f;
  // Maximum horizontal speed component derived from the minimum angle
  float maxXComponent = std::abs(ballSpeed / std::tan(MIN_ANGLE));

  float adjustmentFactor = 0.8f;
  // Calculate the new horizontal velocity based on hit offset
  float newVelocityX = hitOffset * maxXComponent * adjustmentFactor;
  // Calculate the corresponding vertical component, ensuring upward motion
  float newVelocityY = -std::sqrt(
      std::max(0.f, ballSpeed * ballSpeed - newVelocityX * newVelocityX));

  // Enforce a minimum vertical speed to avoid too shallow a trajectory
  float minVerticalSpeed = ballSpeed * std::sin(MIN_ANGLE);
  if (std::abs(newVelocityY) < minVerticalSpeed) {
    newVelocityY = -minVerticalSpeed;
    newVelocityX = (hitOffset >= 0 ? 1.f : -1.f) *
                   std::sqrt(std::max(0.f, ballSpeed * ballSpeed -
                                               newVelocityY * newVelocityY));
  }

  ballVelocity.x = newVelocityX;
  ballVelocity.y = newVelocityY;
}

void Ball::resolveBlockCollision(Block &block,
                                 const sf::FloatRect &currentBounds,
                                 const sf::FloatRect &nextBounds) {
  sf::FloatRect blockBounds = block.getBounds();
  sf::Vector2f currentCenter = currentBounds.getCenter();
  sf::Vector2f nextCenter = nextBounds.getCenter();

  // Compute distances between centers
  float dx = nextCenter.x - blockBounds.getCenter().x;
  float dy = nextCenter.y - blockBounds.getCenter().y;

  // Decide whether the collision is horizontal or vertical
  if (std::abs(dx) * blockBounds.size.y > std::abs(dy) * blockBounds.size.x) {
    // Horizontal collision: adjust X velocity
    ballVelocity.x =
        (dx > 0) ? std::abs(ballVelocity.x) : -std::abs(ballVelocity.x);

    // Adjust position to prevent sticking
    float newX = (dx > 0)
                     ? blockBounds.getCenter().x + blockBounds.size.x / 2.f +
                           currentBounds.size.x / 2.f + 1.f
                     : blockBounds.getCenter().x - blockBounds.size.x / 2.f -
                           currentBounds.size.x / 2.f - 1.f;
    sprite_ptr->setPosition({newX, currentCenter.y});
  } else {
    // Vertical collision: adjust Y velocity
    ballVelocity.y =
        (dy > 0) ? std::abs(ballVelocity.y) : -std::abs(ballVelocity.y);

    // Adjust position to prevent sticking
    float newY = (dy > 0)
                     ? blockBounds.getCenter().y + blockBounds.size.y / 2.f +
                           currentBounds.size.y / 2.f + 1.f
                     : blockBounds.getCenter().y - blockBounds.size.y / 2.f -
                           currentBounds.size.y / 2.f - 1.f;
    sprite_ptr->setPosition({currentCenter.x, newY});
  }

  // Normalize the velocity to maintain constant speed
  float speed = std::sqrt(ballVelocity.x * ballVelocity.x +
                          ballVelocity.y * ballVelocity.y);
  if (speed != 0.f) {
    ballVelocity = (ballVelocity / speed) * ballSpeed;
  }
}

void Ball::onCollision(GameObject &other) {
  auto block = dynamic_cast<Block *>(&other);
  if (!block)
    return;

  sf::FloatRect ballBounds = sprite_ptr->getGlobalBounds();
  sf::FloatRect blockBounds = block->getBounds();

  // Calculate overlap distances using centers
  float overlapX = blockBounds.getCenter().x - ballBounds.getCenter().x;
  float overlapY = blockBounds.getCenter().y - ballBounds.getCenter().y;

  if (std::abs(overlapX) > std::abs(overlapY)) {
    // Horizontal collision: invert X velocity and push out
    ballVelocity.x *= -1;
    if (overlapX > 0)
      sprite_ptr->setPosition({blockBounds.getCenter().x -
                                   blockBounds.size.x / 2.f -
                                   ballBounds.size.x / 2.f,
                               sprite_ptr->getPosition().y});
    else
      sprite_ptr->setPosition({blockBounds.getCenter().x +
                                   blockBounds.size.x / 2.f +
                                   ballBounds.size.x / 2.f,
                               sprite_ptr->getPosition().y});
  } else {
    // Vertical collision: invert Y velocity and push out
    ballVelocity.y *= -1;
    if (overlapY > 0)
      sprite_ptr->setPosition(
          {sprite_ptr->getPosition().x, blockBounds.getCenter().y -
                                            blockBounds.size.y / 2.f -
                                            ballBounds.size.y / 2.f});
    else
      sprite_ptr->setPosition(
          {sprite_ptr->getPosition().x, blockBounds.getCenter().y +
                                            blockBounds.size.y / 2.f +
                                            ballBounds.size.y / 2.f});
  }
}

void Ball::draw(sf::RenderWindow &window) { window.draw(*sprite_ptr); }

sf::FloatRect Ball::getBounds() const { return sprite_ptr->getGlobalBounds(); }

void Ball::attachToPaddle(const sf::Vector2f &paddlePosition) {
  attachedToPaddle = true;
  sf::FloatRect bounds = sprite_ptr->getGlobalBounds();
  sprite_ptr->setPosition(
      {paddlePosition.x, paddlePosition.y - bounds.size.y / 2.f});
}

void Ball::resetVelocity() { ballVelocity = startVelocity; }

bool Ball::isOutOfBounds(float height) {
  if (sprite_ptr->getPosition().y > height) {
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
    // Set an initial upward direction with a slight horizontal offset
    ballVelocity = {0.5f, -1.f};
    float length = std::sqrt(ballVelocity.x * ballVelocity.x +
                             ballVelocity.y * ballVelocity.y);
    if (length != 0.f)
      ballVelocity = (ballVelocity / length) * ballSpeed;
  }
}
