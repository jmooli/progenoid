#pragma once

#include "LevelData.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <map>
#include <string>
class ResourceManager {

public:
  ResourceManager();

  std::shared_ptr<sf::Texture> getTexture(const std::string &key);
  const LevelData &getLevel(const std::string &key) const;

  bool loadLevel(const std::string &filename, const std::string &filepath);
  bool loadTexture(const std::string &filename, const std::string &filepath);

  void loadAllLevelsFromFolder(const std::string &folderPath);
  void loadAllTexturesFromFolder(const std::string &folderPath);

private:
  std::map<std::string, std::shared_ptr<sf::Texture>> textures;
  std::map<std::string, LevelData> loadedLevels;
};
