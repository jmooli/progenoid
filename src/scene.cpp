#include "scene.hpp"
#include "LevelData.hpp"
#include "block_type.hpp"
#include "game_object.hpp"
#include "resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

Scene::Scene(ResourceManager &resources) : resources(resources) {}

void Scene::AddGameObject(std::unique_ptr<GameObject> obj) {
  gameObjects.push_back(std::move(obj));
}

std::unique_ptr<GameObject> createBlock(char type) {}

void Scene::loadLevelFromResource(const std::string &levelKey) {
  const LevelData &data = resources.getLevel(levelKey);

  int rowIndex = 0;

  for (const auto &line : data.gridLines) {
    for (int colIndex = 0; colIndex < (int)line.size(); colIndex++) {
      char c = line[colIndex];
      if (c != '.') {
        AddGameObject(createBlock(c));
      }
    }

    rowIndex++;
  }
}

void Scene::checkCollisions() {
  for (size_t i = 0; i < gameObjects.size(); ++i) {
    for (size_t j = i + 1; j < gameObjects.size(); ++j) {
      auto &obj1 = gameObjects[i];
      auto &obj2 = gameObjects[j];

      if (obj1->collidesWith(*obj2)) {
        obj1->onCollision(*obj2);
        obj2->onCollision(*obj1);
      }
    }
  }
}

void Scene::update(float dt) {
  for (auto &obj : gameObjects) {
    obj->update(dt);
  }

  // This is suboptimal, but for this complexity doesn't matter too much.
  checkCollisions();
}

void Scene::draw(sf::RenderWindow &window) {
  for (auto &obj : gameObjects) {
    obj->draw(window);
  }
}
