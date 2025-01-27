// Copyright Proge 2025

#pragma once

#include "game_object.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System.hpp>
#include <SFML/System/Vector2.hpp>

class Paddle : public GameObject {

public:
  explicit Paddle(float x, float y, float width, float height,
                  const sf::Texture &texture);

  void SetPosition(float x, float y);

  virtual void update(float dt) override;
  virtual void draw(sf::RenderWindow &window) override;

  sf::FloatRect getBounds() const override;
  void onCollision(GameObject &other) override;

  sf::Vector2f GetPosition() const;
  sf::Vector2f GetSize() const;

private:
  sf::Sprite paddleSprite;
};
