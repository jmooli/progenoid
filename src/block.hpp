#pragma once

#include "block_type.hpp"
#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

class Block : public GameObject {

public:
  Block(BlockType type, const sf::Vector2f &position,
        const sf::Texture &texture);

  virtual void update(float dt) override;
  virtual void draw(sf::RenderWindow &window) override;

private:
  BlockType type;
  sf::Sprite sprite;
};
