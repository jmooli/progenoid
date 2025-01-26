// Copy Rights Proge 2025

#include "resource_manager.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>

int main() {

  const unsigned int WINDOW_WIDTH = 1920;
  const unsigned int WINDOW_HEIGHT = 1080;

  auto window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                                 "Progenoid");
  ResourceManager Resources;

  // TODO: take this texture stuff inside of the class
  const sf::Texture &PaddleTexture = Resources.GetTexture("paddle");
  sf::Sprite Paddle(PaddleTexture);

  window.setFramerateLimit(144);

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }

    window.clear();

    Paddle.setPosition(sf::Vector2(500.f, 500.f));
    window.draw(Paddle);

    window.display();
  }
}
