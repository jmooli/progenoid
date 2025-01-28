#pragma once

#include "../entities/game_object.hpp"
#include "LevelData.hpp"
#include "resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <memory>
#include <vector>

class Scene {
public:
  explicit Scene(ResourceManager &rm);

  void AddGameObject(std::unique_ptr<GameObject> obj);

  void update(float deltaTime);
  void draw(sf::RenderWindow &window);

  void loadLevelFromResource(const std::string &levelKey);
  void createWalls(float screenWidth, float screenHeight, float wallThickness);
  void checkCollisions();
  std::unique_ptr<GameObject> createBlockInGridCoordinate(int t, int x, int y);

private:
  std::unique_ptr<LevelData> data;
  int levelFileFormat = 0;
  ResourceManager &resources;
  std::vector<std::unique_ptr<GameObject>> gameObjects;
};
