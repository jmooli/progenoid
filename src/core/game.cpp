#include "game.hpp"
#include "../ui/MainMenu.hpp"
#include "resource_manager.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <iostream>
#include <memory>

Game::Game()
    : window(sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "Progenoid")),
      rm() {

  mainMenu = std::make_unique<MainMenu>(window, [this]() {
    std::cout << "Start Game Button Clicked! Switching to Playing State.\n";
    state = GameState::Playing;
  });
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

    mainMenu->handleEvent(*event);
  }
}

void Game::update(float dt) {
  if (gameIsPaused()) {
    return;
  };
  // Safely call update on currentScene
  if (state == GameState::Playing && currentScene) {
    currentScene->update(dt);
  }
}

void Game::render() {
  window.clear();
  if (state == GameState::Playing && currentScene) {
    currentScene->draw(window);
  }
  if (state == GameState::MainMenu && mainMenu) {
    mainMenu->draw();
  }
  if (state == GameState::LevelEditor && currentScene) {
    // Draw level editor components here
  }
  window.display();
}
