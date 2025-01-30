#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow &win, ResourceManager &resourceManager,
                   std::function<void()> startGameCallback)
    : window(win) {

  if (!font.openFromFile("assets/fonts/ZenDots-Regular.ttf")) {
    std::cerr << "Failed to load font!\n";
  }

  auto buttonTexture = resourceManager.getTexture("b_normal");
  auto buttonHoverTexture = resourceManager.getTexture("b_hover");

  // TODO: Should check if the textures are actually retrieved. !!!

  startGameButton = std::make_unique<Button>(
      sf::Vector2f(win.getSize().x / 2.f - 250.f, 200.f),
      sf::Vector2f(1.f, 1.f), "Start Game", font, *buttonTexture,
      *buttonHoverTexture, startGameCallback);

  levelEditorButton = std::make_unique<Button>(
      sf::Vector2f(win.getSize().x / 2.f - 250.f, 350.f),
      sf::Vector2f(1.f, 1.f), "Level Editor", font, *buttonTexture,
      *buttonHoverTexture,
      [&]() { std::cout << "Level Editor Button Clicked!\n"; });

  quitButton = std::make_unique<Button>(
      sf::Vector2f(win.getSize().x / 2.f - 250.f, 500.f),
      sf::Vector2f(1.f, 1.f), "Quit", font, *buttonTexture, *buttonHoverTexture,
      [&]() {
        std::cout << "Quit Button Clicked! Exiting...\n";
        window.close();
      });
}

void MainMenu::handleEvent(const sf::Event &event) {
  if (startGameButton)
    startGameButton->handleEvent(event, window);
  if (levelEditorButton)
    levelEditorButton->handleEvent(event, window);
  if (quitButton)
    quitButton->handleEvent(event, window);
}

void MainMenu::update(float dt) {
  // Nothing to update atm.
}

void MainMenu::draw() {
  if (startGameButton)
    startGameButton->draw(window);
  if (levelEditorButton)
    levelEditorButton->draw(window);
  if (quitButton)
    quitButton->draw(window);
}
