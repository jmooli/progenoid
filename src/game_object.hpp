#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class GameObject {

public:
  virtual ~GameObject() = default;

  virtual void Update(float DeltaTime);
  virtual void Draw(sf::RenderWindow &Window);
};
