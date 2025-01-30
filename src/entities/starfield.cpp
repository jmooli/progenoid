#include "starfield.hpp"
#include <cstdlib>

Starfield::Starfield(unsigned int numStars) {
  for (unsigned int i = 0; i < numStars; ++i) {
    float x = static_cast<float>(rand() % 1920);
    float y = static_cast<float>(rand() % 1080);
    float speed = 0.2f + static_cast<float>(rand() % 25);
    float size = 1.f + static_cast<float>(rand() % 3);

    sf::Color color = sf::Color(190, 190, 255, 255 - (speed * 10.f));

    stars.emplace_back(x, y, speed, size, color);
  }
}

void Starfield::update(float dt, float paddleOffset) {
  for (auto &star : stars) {
    star.update(dt, paddleOffset);

    if (star.isOffScreen()) {
      float newX = static_cast<float>(rand() % 1920);
      star.reset(newX, 0);
    }
  }
}

void Starfield::draw(sf::RenderWindow &window) {
  for (auto &star : stars) {
    star.draw(window);
  }
}
