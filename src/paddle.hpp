// Copyright Proge 2025

#pragma once

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

class Paddle : public GameObject {

public:
  explicit Paddle(const sf::Texture &texture);

  void SetPosition(float x, float y);

  virtual void Update(float deltaTime) override;
  virtual void Draw(sf::RenderWindow &window) override;

  sf::Vector2f GetPosition() const;
  sf::Vector2f GetSize() const;

private:
  sf::Sprite paddleSprite;
};
