#include "./paddle.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

Paddle::Paddle(const sf::Texture &texture)
    : paddleSprite(texture) // pass in texture
{
  paddleSprite.setPosition(sf::Vector2f(1920.f / 2.f, 1000.f));
}

void Paddle::SetPosition(float x, float y) {

  paddleSprite.setPosition(sf::Vector2(x, y));
}

void Paddle::Update(float deltaTime) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) ||
      sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
    paddleSprite.move(sf::Vector2f(-100.f * deltaTime, 0.f));
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) ||
             sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
    paddleSprite.move(sf::Vector2f(100.f * deltaTime, 0.f));
  }
}

void Paddle::Draw(sf::RenderWindow &window) { window.draw(paddleSprite); }

sf::Vector2f Paddle::GetPosition() const { return paddleSprite.getPosition(); }

sf::Vector2f Paddle::GetSize() const {
  auto bounds = paddleSprite.getLocalBounds();
  auto scale = paddleSprite.getScale();
  return {bounds.size.x * scale.x, bounds.size.y * scale.y};
}
