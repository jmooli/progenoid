#include "game.hpp"
#include "resource_manager.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>

Game::Game()
    : window(sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Progenoid")),
      rm() {
  currentScene = std::make_unique<Scene>(rm);

  window.setFramerateLimit(144);
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
  while (const std::optional event = window.pollEvent()) {
    if (event->is<sf::Event::Closed>()) {
      window.close();
    }
  }
}

void Game::update(float dt) {
  // Safely call update on currentScene
  if (currentScene) {
    currentScene->update(dt);
  }
}

void Game::render() {
  window.clear();
  if (currentScene) {
    currentScene->draw(window);
  }
  window.display();
}
