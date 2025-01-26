#include "./paddle.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/System/Vector2.hpp>

Paddle::Paddle(const sf::Texture &texture)
    : PaddleSprite(texture) // pass in texture
{
  // TODO:init
}

void Paddle::SetPosition(float x, float y) {

  PaddleSprite.setPosition(sf::Vector2(x, y));
}

void Paddle::Update(float DeltaTime) {}

void Paddle::Draw(sf::RenderTarget &target) const { target.draw(PaddleSprite); }

sf::Vector2f Paddle::GetPosition() const { return PaddleSprite.getPosition(); }

sf::Vector2f Paddle::GetSize() const {
  auto bounds = PaddleSprite.getLocalBounds();
  auto scale = PaddleSprite.getScale();
  return {bounds.size.x * scale.x, bounds.size.y * scale.y};
}
