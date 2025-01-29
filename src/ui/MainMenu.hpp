#pragma once
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class MainMenu {
public:
  MainMenu(sf::RenderWindow &window, std::function<void()> startGameCallback);

  void handleEvent(const sf::Event &event);
  void update(float dt);
  void draw();

private:
  sf::RenderWindow &window;
  sf::Font font;

  Button startGameButton;
  Button levelEditorButton;
  Button quitButton;
};
