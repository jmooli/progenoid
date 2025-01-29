#include "scene.hpp"
#include "../entities/ball.hpp"
#include "../entities/block.hpp"
#include "../entities/game_object.hpp"
#include "../entities/paddle.hpp"
#include "../entities/wall.hpp"
#include "LevelData.hpp"
#include "resource_manager.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <memory>
#include <string>

Scene::Scene(ResourceManager &rm) : resources(rm) {
  loadLevelFromResource("level1");

  std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(
      1920.f / 2, 1000, 500.f, 50.f, rm.getTexture("Paddle"));
  std::unique_ptr<Ball> ball =
      std::make_unique<Ball>(1920.f / 2, 1000 - 25.f, 15.f, 300.f, -300.f);

  ball->attachToPaddle(paddle->getAttachmentPoint());

  AddGameObject(std::move(paddle));
  AddGameObject(std::move(ball));
  // createWalls(1920.f, 1080.f, 20.f);
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
  const float X_SPACING = 20.f;
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

bool Scene::allBlocksDestroyed() const {
  for (const auto &obj : gameObjects) {
    if (dynamic_cast<Block *>(obj.get()) &&
        !static_cast<Block *>(obj.get())->isDestroyed()) {
      return false;
    }
  }
  return true;
}

void Scene::restartLevel(const std::string &levelKey) {
  gameObjects.clear();
  loadLevelFromResource(levelKey);

  // Recreate paddle and ball
  std::unique_ptr<Paddle> paddle = std::make_unique<Paddle>(
      1920.f / 2, 1000, 500.f, 50.f, resources.getTexture("Paddle"));
  Paddle *paddlePtr = paddle.get();
  AddGameObject(std::move(paddle));

  std::unique_ptr<Ball> ball = std::make_unique<Ball>(
      paddlePtr->getAttachmentPoint().x,
      paddlePtr->getAttachmentPoint().y - 25.f, 15.f, 300.f, -300.f);
  ball->attachToPaddle(paddlePtr->getAttachmentPoint());
  AddGameObject(std::move(ball));

  std::cout << "Level restarted.\n";
}

void Scene::createWalls(float screenWidth, float screenHeight,
                        float wallThickness) {
  AddGameObject(std::make_unique<Wall>(0.f, 0.f, screenWidth, wallThickness));
  AddGameObject(std::make_unique<Wall>(0.f, 0.f, wallThickness, screenHeight));
  AddGameObject(std::make_unique<Wall>(screenWidth - wallThickness, 0.f,
                                       wallThickness, screenHeight));
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

void Scene::checkCollisions() {
  for (size_t i = 0; i < gameObjects.size(); ++i) {
    for (size_t j = i + 1; j < gameObjects.size(); ++j) {
      auto &obj1 = gameObjects[i];
      auto &obj2 = gameObjects[j];

      bool bothWalls = (dynamic_cast<Wall *>(obj1.get()) != nullptr) &&
                       (dynamic_cast<Wall *>(obj2.get()) != nullptr);

      if (bothWalls)
        continue;

      if (obj1->collidesWith(*obj2)) {

        //  std::cout << "Collision: " << typeid(*obj1).name() << " vs "
        //          << typeid(*obj2).name() << "\n";
        obj1->onCollision(*obj2);
        obj2->onCollision(*obj1);
      }
    }
  }
}

void Scene::update(float dt) {
  const int subSteps = 4;
  float subDt = dt / subSteps;

  for (int step = 0; step < subSteps; ++step) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {
      for (auto &obj : gameObjects) {
        auto ball = dynamic_cast<Ball *>(obj.get());
        if (ball) {
          ball->launch();
        }
      }
    }

    Paddle *paddle = nullptr;
    Ball *ball = nullptr;

    for (auto &obj : gameObjects) {
      if (!paddle) {
        paddle = dynamic_cast<Paddle *>(obj.get());
      }
      if (!ball) {
        ball = dynamic_cast<Ball *>(obj.get());
      }
      if (paddle && ball) {
        break;
      }
    }

    if (paddle && ball && ball->attachedToPaddle) {
      ball->attachToPaddle(paddle->getAttachmentPoint());
    }
    for (auto &obj : gameObjects) {
      obj->update(subDt);
    }

    checkCollisions();
  }
  // After substeps, check if the ball is out of bounds
  for (auto &obj : gameObjects) {
    auto ball = dynamic_cast<Ball *>(obj.get());
    if (ball && ball->isOutOfBounds(1080.f)) { // Assuming screen height is 1080
      // Find the paddle to reattach
      Paddle *paddle = nullptr;
      for (auto &pObj : gameObjects) {
        paddle = dynamic_cast<Paddle *>(pObj.get());
        if (paddle)
          break;
      }

      if (paddle) {
        ball->attachToPaddle(paddle->getAttachmentPoint());
        ball->resetVelocity();
        std::cout << "Ball reattached after going out of bounds.\n";
      }
    }
  }

  // Check if all blocks are destroyed to restart or load a new level
  if (allBlocksDestroyed()) {
    std::cout << "All blocks destroyed! Restarting level.\n";
    restartLevel(
        "level1"); // Replace "level1" with the next level key if applicable
  }

  removeDestoryed();
}

void Scene::removeDestoryed() {

  gameObjects.erase(
      std::remove_if(gameObjects.begin(), gameObjects.end(),
                     [](const std::unique_ptr<GameObject> &obj) -> bool {
                       auto block = dynamic_cast<Block *>(obj.get());
                       return block && block->isDestroyed();
                     }),
      gameObjects.end());
}

void Scene::draw(sf::RenderWindow &window) {
  for (auto &obj : gameObjects) {
    obj->draw(window);
  }
}
