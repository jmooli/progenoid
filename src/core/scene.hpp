#pragma once

#include "../entities/game_object.hpp"
#include "../entities/starfield.hpp"
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

  void update(float dt);
  void draw(sf::RenderWindow &window);
  void restartLevel(const std::string &levelKey);

private:
  void loadLevelFromResource(const std::string &levelKey);
  std::unique_ptr<GameObject> createBlockInGridCoordinate(int t, int x, int y);
  std::unique_ptr<LevelData> data;
  ResourceManager &resources;
  std::vector<std::unique_ptr<GameObject>> gameObjects;
  Starfield starfield;

  int levelFileFormat = 0;
};
