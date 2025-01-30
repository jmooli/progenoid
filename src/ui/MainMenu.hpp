#pragma once
#include "../core/resource_manager.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class MainMenu {
public:
  MainMenu(sf::RenderWindow &win, ResourceManager &resourceManager,
           std::function<void()> startGameCallback);

  void handleEvent(const sf::Event &event);
  void update(float dt);
  void draw();

private:
  sf::RenderWindow &window;
  sf::Font font;

  std::unique_ptr<Button> startGameButton;
  std::unique_ptr<Button> levelEditorButton;
  std::unique_ptr<Button> quitButton;

  std::shared_ptr<sf::Texture> buttonTexture;
  std::shared_ptr<sf::Texture> buttonHoverTexture;
};
