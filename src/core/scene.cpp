#include "scene.hpp"
#include "../entities/ball.hpp"
#include "../entities/block.hpp"
#include "../entities/game_object.hpp"
#include "../entities/paddle.hpp"
#include "LevelData.hpp"
#include "resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

Scene::Scene(ResourceManager &rm, sf::RenderWindow &window)
    : resources(rm), starfield(200), window(window) {

  loadLevelFromResource("level1");

  std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(
      1920.f / 2, 1000, 500.f, 50.f, *rm.getTexture("paddle"));
  std::unique_ptr<Ball> ball =
      std::make_unique<Ball>(10, *rm.getTexture("ball"),
                             paddle->getAttachmentPoint(), window.getSize());

  ball->attachToPaddle(paddle->getAttachmentPoint());

  AddGameObject(std::move(paddle));
  AddGameObject(std::move(ball));
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
  const float B_WIDTH = 150.f;
  const float B_HEIGHT = 55.f;
  const float X_SPACING = 2.f;
  const float Y_SPACING = 2.f;
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

void Scene::restartLevel(const std::string &levelKey) {
  gameObjects.clear();
  loadLevelFromResource(levelKey);

  // Recreate paddle and ball
  std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(
      1920.f / 2, 1000, 500.f, 50.f, *resources.getTexture("paddle"));
  Paddle *paddlePtr = paddle.get();
  AddGameObject(std::move(paddle));

  std::unique_ptr<Ball> ball =
      std::make_unique<Ball>(10, *resources.getTexture("ball"),
                             paddle->getAttachmentPoint(), window.getSize());
  ball->attachToPaddle(paddlePtr->getAttachmentPoint());
  AddGameObject(std::move(ball));

  std::cout << "Level restarted.\n";
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
        int t = c - '0';
        AddGameObject(createBlockInGridCoordinate(t, colIndex, rowIndex));
      }
    }
    rowIndex++;
  }
}

void Scene::update(float dt) {
  Paddle *paddle = nullptr;
  for (auto &obj : gameObjects) {
    paddle = dynamic_cast<Paddle *>(obj.get());
    if (paddle)
      break;
  }

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
    for (auto &obj : gameObjects) {
      auto ball = dynamic_cast<Ball *>(obj.get());
      if (ball) {
        ball->launch();
      }
    }
  }

  if (!paddle) {
    std::cerr << "Error: Paddle not found in gameObjects!\n";
    return;
  }

  starfield.update(
      dt, ((paddle->GetPosition().x - window.getSize().x * 0.5f) * 0.01f));

  for (auto &obj : gameObjects) {
    obj->update(dt, *paddle, gameObjects);
  }
}

void Scene::draw(sf::RenderWindow &window) {
  starfield.draw(window);

  for (auto &obj : gameObjects) {
    obj->draw(window);
  }
}
