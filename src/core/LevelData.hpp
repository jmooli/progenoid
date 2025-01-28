#pragma once
#include <string>
#include <vector>

struct LevelData {
  int version = 0;
  std::vector<std::string> gridLines;
  int cols = 0;
  int rows = 0;
  // std::string musicKey;
};
