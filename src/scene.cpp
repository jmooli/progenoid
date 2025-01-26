#include "scene.hpp"
#include "LevelData.hpp"
#include "game_object.hpp"
#include "resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <memory>

Scene::Scene(ResourceManager &resources) : resources(resources) {}

void Scene::AddGameObject(std::unique_ptr<GameObject> obj) {

  gameObjects.push_back(std::move(obj));
}

void Scene::loadLevelFromResource(const std::string &levelKey) {
  const LevelData &data = resources.getLevel(levelKey);
}

void Scene::update(float dt) {
  for (auto &obj : gameObjects) {
    obj->update(dt);
  }
}

void Scene::draw(sf::RenderWindow &window) {
  for (auto &obj : gameObjects) {
    obj->draw(window);
  }
}
