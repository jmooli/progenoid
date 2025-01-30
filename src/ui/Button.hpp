#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <functional>

class Button {
public:
  Button(const sf::Vector2f &position, const sf::Vector2f &size,
         const std::string &text, sf::Font &font, sf::Texture &texture,
         sf::Texture &mouseOverTexture, std::function<void()> onClick);

  void handleEvent(const sf::Event &event, const sf::RenderWindow &window);
  void draw(sf::RenderWindow &window);

  void startGame();
  void quitGame();
  void openLevelEditor();

private:
  sf::Sprite sprite;
  sf::Text buttonText;

  const sf::Texture texture;
  const sf::Texture mouseOverTexture;

  std::function<void()> onClickCallback;

  bool isMouseOver(const sf::RenderWindow &window) const;
};
