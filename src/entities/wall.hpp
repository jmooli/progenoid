#pragma once

#include "game_object.hpp"
#include <SFML/Graphics/RectangleShape.hpp>

class Wall : public GameObject {
public:
  Wall(float x, float y, float width, float height);

  void update(float dt) override;
  void draw(sf::RenderWindow &window) override;
  sf::FloatRect getBounds() const override;
  void onCollision(GameObject &other) override;

private:
  sf::RectangleShape shape;
};
