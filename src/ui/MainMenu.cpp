#include "MainMenu.hpp"
#include <iostream>

MainMenu::MainMenu(sf::RenderWindow &win,
                   std::function<void()> startGameCallback)
    : window(win),
      startGameButton(sf::Vector2f(win.getSize().x / 2.f - 250.f, 200.f),
                      sf::Vector2f(500.f, 100.f), "Start Game", font,
                      startGameCallback),
      levelEditorButton(sf::Vector2f(win.getSize().x / 2.f - 250.f, 350.f),
                        sf::Vector2f(500.f, 100.f), "Level Editor", font,
                        [&]() {
                          std::cout << "Level Editor Button Clicked!\n";
                          // Implement level editor logic here
                        }),
      quitButton(sf::Vector2f(win.getSize().x / 2.f - 250.f, 500.f),
                 sf::Vector2f(500.f, 100.f), "Quit", font, [&]() {
                   std::cout << "Quit Button Clicked! Exiting...\n";
                   window.close();
                 }) {
  if (!font.openFromFile("assets/fonts/ZenDots-Regular.ttf")) {
    std::cerr << "Failed to load font!\n";
  }
}

void MainMenu::handleEvent(const sf::Event &event) {
  startGameButton.handleEvent(event, window);
  levelEditorButton.handleEvent(event, window);
  quitButton.handleEvent(event, window);
}

void MainMenu::update(float dt) {}

void MainMenu::draw() {
  startGameButton.draw(window);
  levelEditorButton.draw(window);
  quitButton.draw(window);
}
