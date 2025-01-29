#pragma once

#include "../ui/MainMenu.hpp"
#include "resource_manager.hpp"
#include "scene.hpp"
#include <SFML/Graphics.hpp>
#include <memory>

enum class GameState {
  MainMenu,
  Playing,
  LevelEditor,
};

class Game {
public:
  Game();
  void run();

  ResourceManager &getResourceManager() { return rm; }

  void pauseGame() { isPaused = true; };
  void resumeGame() { isPaused = false; };
  bool gameIsPaused() const { return isPaused; };

private:
  bool isPaused = false;

  sf::RenderWindow window;

  ResourceManager rm;

  std::unique_ptr<Scene> currentScene;
  std::unique_ptr<MainMenu> mainMenu;

  const unsigned int WINDOW_WIDTH = 1920;
  const unsigned int WINDOW_HEIGHT = 1080;

  void processEvents();
  void update(float dt);
  void render();

  int score = 0;
  int lives = 3;

  GameState state = GameState::MainMenu;
};
