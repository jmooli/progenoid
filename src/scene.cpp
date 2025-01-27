#include "scene.hpp"
#include "LevelData.hpp"
#include "block.hpp"
#include "game_object.hpp"
#include "paddle.hpp"
#include "resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <memory>

Scene::Scene(ResourceManager &rm) : resources(rm) {
  loadLevelFromResource("level1");

  // make paddle
  AddGameObject(std::make_unique<Paddle>(1920.f / 2, 1000, 500.f, 50.f,
                                         rm.getTexture("Paddle")));
}

void Scene::AddGameObject(std::unique_ptr<GameObject> obj) {
  gameObjects.push_back(std::move(obj));
}

std::unique_ptr<GameObject> Scene::createBlockInGridCoordinate(int t, int x,
                                                               int y) {

  if (!data) {
    return nullptr;
  }

  // I should figure out smarter system for these.
  const float B_WIDTH = 200.f;
  const float B_HEIGHT = 75.f;
  const float X_SPACING = 50.f;
  const float Y_SPACING = 20.f;
  const float SCREEN_WIDTH = 1920.f;
  const float SCREEN_HEIGHT = 1080.f;

  float gridWidth = data->cols * B_WIDTH + (data->cols - 1) * X_SPACING;
  float gridHeight = data->rows * B_HEIGHT + (data->rows - 1) * Y_SPACING;

  float screenX = (SCREEN_WIDTH - gridWidth) / 2;
  float screenY = B_HEIGHT;

  float x_position = screenX + x * (B_WIDTH + X_SPACING);
  float y_position = screenY + y * (B_HEIGHT + Y_SPACING);

  auto block =
      std::make_unique<Block>(t, x_position, y_position, B_WIDTH, B_HEIGHT);

  return block;
}

void Scene::loadLevelFromResource(const std::string &levelKey) {
  data = std::make_unique<LevelData>(resources.getLevel(levelKey));

  if (!data) {
    return;
  }

  int rowIndex = 0;

  for (const auto &line : data->gridLines) {
    for (int colIndex = 0; colIndex < (int)line.size(); colIndex++) {
      char c = line[colIndex];
      if (c != '.') {
        int t = (int)c;
        AddGameObject(createBlockInGridCoordinate(t, rowIndex, colIndex));
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
  // For this game would be enough to do it Ball.
  checkCollisions();
}

void Scene::draw(sf::RenderWindow &window) {
  for (auto &obj : gameObjects) {
    obj->draw(window);
  }
}
