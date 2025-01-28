#pragma once

enum class BlockType {
  None = 0,
  Type1,
  Type2,
};

inline BlockType charToBlockType(char c) {
  switch (c) {
  case '.':
    return BlockType::None;
  case '1':
    return BlockType::Type1;
  case '2':
    return BlockType::Type2;
  default:
    return BlockType::None;
  }
}
