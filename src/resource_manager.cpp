#include "resource_manager.hpp"
#include "LevelData.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

ResourceManager::ResourceManager() {
  loadAllLevelsFromFolder(std::string("levels"));
  loadAllTexturesFromFolder(std::string("assets"));
};

void ResourceManager::loadAllLevelsFromFolder(const std::string &folderPath) {
  try {
    for (const auto &entry : fs::directory_iterator(folderPath)) {
      if (!entry.is_regular_file()) {
        continue;
      }

      std::string filepath = entry.path().string();
      std::string filename = entry.path().filename().string();
      std::string stem = entry.path().stem();

      if (!loadLevel(stem, filepath)) {
        std::cerr << "Skipping level file: " << filepath << "\n";
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error while iterating folder " << folderPath << " : "
              << e.what() << "\n";
  }
}

void ResourceManager::loadAllTexturesFromFolder(const std::string &folderPath) {
  try {
    for (const auto &entry : fs::directory_iterator(folderPath)) {
      if (!entry.is_regular_file()) {
        continue;
      }

      // Check extension
      auto extension = entry.path().extension().string();
      if (extension != ".png" && extension != ".jpg" && extension != ".jpeg" &&
          extension != ".bmp" && extension != ".gif") {
        // skip non image files => skip
        continue;
      }

      std::string filepath = entry.path().string();
      std::string stem = entry.path().stem().string();

      if (!loadTexture(stem, filepath)) {
        std::cerr << "Skipping texture file: " << filepath << "\n";
      }
    }
  } catch (const std::exception &e) {
    std::cerr << "Error while iterating folder " << folderPath << " : "
              << e.what() << "\n";
  }
}

bool ResourceManager::loadLevel(const std::string &key,
                                const std::string &filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to open level file: " << filepath << "\n";
    return false;
  }

  LevelData levelData;
  std::string line;

  // Check for the version
  if (std::getline(file, line)) {
    if (line.rfind("Version:", 0) == 0) {
      std::string versionStr = line.substr(8);
      try {
        levelData.version = std::stoi(versionStr);
      } catch (...) {
        levelData.version = 0;
      }
    } else {
      levelData.version = 0;
      file.seekg(0);
    }
  }

  while (std::getline(file, line)) {
    levelData.gridLines.push_back(line);
  }

  loadedLevels.insert({key, std::move(levelData)});
  return true;
}

bool ResourceManager::loadTexture(const std::string &key,
                                  const std::string &filepath) {

  sf::Texture Texture;

  if (!Texture.loadFromFile(filepath)) {
    std::cerr << "Failed to load texture" << filepath << "\n";
    return false;
  }
  loadedTextures.insert({key, std::move(Texture)});
  return true;
}

const sf::Texture &ResourceManager::getTexture(const std::string &key) const {
  auto it = loadedTextures.find(key);
  if (it == loadedTextures.end()) {
    throw std::runtime_error("Texture not found: " + key);
  }
  return it->second;
}

const LevelData &ResourceManager::getLevel(const std::string &key) const {
  auto it = loadedLevels.find(key);
  if (it == loadedLevels.end()) {
    throw std::runtime_error("LevelData not found: " + key);
  }
  return it->second;
}
