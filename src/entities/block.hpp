#pragma once

#include "game_object.hpp"
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Block : public GameObject {
public:
  Block(int type, float x, float y, float width, float height);

  int health = 1;
  void update(float deltaTime) override;
  void draw(sf::RenderWindow &window) override;
  sf::FloatRect getBounds() const override;
  void onCollision(GameObject &other) override;

  void updateColor();

  bool isDestroyed() const { return destroyed; }

private:
  sf::RectangleShape shape;

  bool destroyed = false;
};
