#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {

public:
  virtual ~GameObject();

  virtual void update(float dt) = 0;
  virtual void draw(sf::RenderWindow &window) = 0;

  virtual sf::FloatRect getBounds() const = 0;
  bool collidesWith(const GameObject &other) const {
    return getBounds().findIntersection(other.getBounds());
  }

  virtual void onCollision(GameObject &other) = 0;
};
