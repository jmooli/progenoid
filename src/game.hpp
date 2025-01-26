#pragma once
#include "resource_manager.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

class Game {
public:
  Game();
  void run();

  ResourceManager &getResourceManager() { return resources; }

private:
  sf::RenderWindow window;

  ResourceManager resources;

  void processEvents();
  void update(float dt);
  void render();

  std::unique_ptr<Scene> currentScene;

  const unsigned int WINDOW_WIDTH = 1920;
  const unsigned int WINDOW_HEIGHT = 1080;
};
