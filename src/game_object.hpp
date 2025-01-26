#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {

public:
  virtual ~GameObject() = default;

  virtual void update(float dt);
  virtual void draw(sf::RenderWindow &window);
};
