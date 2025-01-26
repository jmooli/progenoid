#include "resource_manager.hpp"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

const std::pair<std::string, std::string> ResourceManager::Assets[] = {
    {"paddle", "assets/Paddle.png"}, {"ball", "assets/ball.png"}};

ResourceManager::ResourceManager() { LoadAll(); };

void ResourceManager::LoadAll() {
  for (auto &[key, filename] : Assets) {
    sf::Texture Texture;
    if (!Texture.loadFromFile(filename)) {
      std::cerr << "Failed to load " << filename << "\n";
    }
    LoadedTextures.insert({key, std::move(Texture)});
  }
}

const sf::Texture &ResourceManager::GetTexture(const std::string &key) const {
  auto it = LoadedTextures.find(key);
  if (it == LoadedTextures.end()) {
    throw std::runtime_error("Texture not found: " + key);
  }
  return it->second;
}
