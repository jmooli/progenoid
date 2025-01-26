#pragma once

#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
class ResourceManager {

public:
  ResourceManager();

  const sf::Texture &GetTexture(const std::string &key) const;

private:
  static const std::pair<std::string, std::string> Assets[];

  void LoadAll();

  std::map<std::string, sf::Texture> LoadedTextures;
};
