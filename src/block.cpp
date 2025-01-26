#include "block.hpp"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

Block::Block(BlockType type, const sf::Vector2f &position,
             const sf::Texture &texture)
    : type(type), sprite(texture) {

  // TODO:set other properties
  //
  sprite
      .setSca

          sprite.setPosition(position);
}

void Block::update(float dt) {
  // currently nothing to update
}

void Block::draw(sf::RenderWindow &window) { window.draw(sprite); }
