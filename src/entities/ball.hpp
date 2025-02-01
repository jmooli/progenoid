#pragma once

#include "game_object.hpp"
#include "paddle.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

class Block;

class Ball : public GameObject {
public:
  Ball(int radius, const sf::Texture &texture, sf::Vector2f position,
       sf::Vector2u windowSize);

  // GameObject interface
  void update(float dt, Paddle &paddle,
              std::vector<std::unique_ptr<GameObject>> &gameObjects) override;
  void draw(sf::RenderWindow &window) override;
  sf::FloatRect getBounds() const override;
  void onCollision(GameObject &other) override;

  // Ball-specific methods
  void attachToPaddle(const sf::Vector2f &paddlePosition);
  void resetVelocity();
  bool isOutOfBounds(float height);
  void launch();

private:
  // Rendering sprite
  std::unique_ptr<sf::Sprite> sprite_ptr;

  // Current velocity of the ball
  sf::Vector2f ballVelocity;

  // Window boundaries for collision handling
  sf::Vector2u windowSize;

  // Constant ball speed (set in constructor)
  float ballSpeed = 400.f;

  // Starting position and velocity for resets
  sf::Vector2f startPos;
  sf::Vector2f startVelocity;

  // State flag to indicate whether the ball is attached to the paddle
  bool attachedToPaddle = true;

  // Helper functions
  void applyAngleDeflection(Paddle &paddle);
  bool checkCollision(const sf::FloatRect &otherBounds, float deltaTime);
  void handleWallCollision(sf::Vector2f &nextCenter,
                           const sf::FloatRect &bounds);
  bool handlePaddleCollision(Paddle &paddle, float subDt,
                             sf::Vector2f &nextCenter,
                             const sf::FloatRect &currentBounds);
  bool
  handleBlockCollisions(std::vector<std::unique_ptr<GameObject>> &gameObjects,
                        float subDt, sf::Vector2f &nextCenter,
                        const sf::FloatRect &currentBounds);
  void resolveBlockCollision(Block &block, const sf::FloatRect &currentBounds,
                             const sf::FloatRect &nextBounds);
};
