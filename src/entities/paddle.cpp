#include "./paddle.hpp"
#include "game_object.hpp"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <memory>

Paddle::Paddle(float x, float y, float width, float height,
               const sf::Texture &texture)
    : paddleSprite(texture) // pass in texture
{
  paddleSprite.setPosition(sf::Vector2f(1920.f / 2.f, 1000.f));
}

void Paddle::SetPosition(float x, float y) {

  paddleSprite.setPosition(sf::Vector2(x, y));
}

void Paddle::update(float deltaTime, Paddle &paddle,
                    std::vector<std::unique_ptr<GameObject>> &gameObjects) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    paddleSprite.move(sf::Vector2f(-speed * deltaTime, 0.f));
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    paddleSprite.move(sf::Vector2f(speed * deltaTime, 0.f));
  }
}

void Paddle::draw(sf::RenderWindow &window) { window.draw(paddleSprite); }

sf::Vector2f Paddle::GetPosition() const { return paddleSprite.getPosition(); }

sf::Vector2f Paddle::GetSize() const {
  auto bounds = paddleSprite.getLocalBounds();
  auto scale = paddleSprite.getScale();
  return {bounds.size.x * scale.x, bounds.size.y * scale.y};
}

sf::Vector2f Paddle::getAttachmentPoint() const {
  sf::Vector2f paddlePosition = paddleSprite.getPosition();
  return {paddlePosition.x + (GetSize().x / 2),
          paddlePosition.y - GetSize().y / 2};
}

sf::FloatRect Paddle::getBounds() const {
  auto bounds = paddleSprite.getGlobalBounds();
  return bounds;
}

void Paddle::onCollision(GameObject &other) {}
