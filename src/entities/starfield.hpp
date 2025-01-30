#pragma once
#include "star.hpp"
#include <vector>

class Starfield {
public:
  Starfield(unsigned int numStars);
  void update(float dt, float paddleOffset);
  void draw(sf::RenderWindow &window);

private:
  std::vector<Star> stars;
};
