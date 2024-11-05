#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

constexpr uint8_t BLOCK_ROWS = 3;
constexpr uint8_t BLOCK_COLS = 4;
constexpr float BLOCK_POS = 50.0f;
constexpr float BLOCK_WIDTH = 100.0f;
constexpr float BLOCK_HEIGHT = 40.0f;
constexpr float BLOCK_OFFSET = 30.0f;

class Blocks {
 public:
  Blocks() {
    blocks.resize(BLOCK_ROWS);
    for (auto& row : blocks)
      row.resize(BLOCK_COLS);
    GenerateBlocks();
  };

  void Draw(sf::RenderTarget& rt) {
    for (std::vector<sf::RectangleShape>& blockVec : blocks) {
      for (sf::RectangleShape& block : blockVec) {
        rt.draw(block);
      }
    }
  }

  void RemoveBlock(size_t row, size_t col) {
    blocks[row].erase(blocks[row].begin() + col);
  }

  std::vector<std::vector<sf::RectangleShape>>& GetBlocks() { return blocks; }

  void GenerateBlocks() {
    sf::Vector2f pos = {BLOCK_POS, BLOCK_POS};
    for (size_t i = 0; i < BLOCK_ROWS; i++) {
      for (size_t j = 0; j < BLOCK_COLS; j++) {
        sf::RectangleShape rect({BLOCK_WIDTH, BLOCK_HEIGHT});
        rect.setPosition(pos);
        blocks[i][j] = rect;
        pos.x += BLOCK_WIDTH + BLOCK_OFFSET;
      }
      pos.y += BLOCK_HEIGHT + BLOCK_OFFSET;
      pos.x = BLOCK_POS;
    }
  }

 private:
  std::vector<std::vector<sf::RectangleShape>> blocks;
};
