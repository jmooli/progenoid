// Copy Rights Proge 2025

#include "game.hpp"
#include "resource_manager.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>

Game::Game() {
  window = sf::RenderWindow(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
                            "Progenoid");
  resources = ResourceManager();
  window.setFramerateLimit(60);
}

void Game::run() {
  sf::Clock clock;
  while (window.isOpen()) {
    processEvents();
    float dt = clock.restart().asSeconds();
    update(dt);
    render();
  }
}

void Game::processEvents() {

  while (window.isOpen()) {
    while (const std::optional event = window.pollEvent()) {
      if (event->is<sf::Event::Closed>()) {
        window.close();
      }
    }
  }
}

void Game::update(float dt) {
  // Scene handles object udpates
  currentScene->update(dt);
}

void Game::render() {
  window.clear();
  currentScene->draw(window);
  window.display();
}
