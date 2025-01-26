#pragma once

#include "game_object.hpp"
#include "resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>
#include <vector>

class Scene {
public:
  explicit Scene(ResourceManager &resources);

  void AddGameObject(std::unique_ptr<GameObject> obj);

  void update(float deltaTime);
  void draw(sf::RenderWindow &window);

  void loadLevelFromResource(const std::string &levelKey);

private:
  int levelFileFormat = 0;
  ResourceManager &resources;
  std::vector<std::unique_ptr<GameObject>> gameObjects;
};
