#pragma once

#include <Blocks.hpp>
#include <Player.hpp>

constexpr float BALL_SIZE = 16.0f;
constexpr float BALL_SPEED = 300.0f;

class Ball {
 public:
  Ball(const sf::Vector2f& pos) : originalPosition(pos) {
    ball.setSize({BALL_SIZE, BALL_SIZE});
    ball.setPosition(pos);
  }

  void Draw(sf::RenderTarget& rt) const {
    rt.draw(ball);
  }
  void SetDirection(const sf::Vector2f& dir) {
    velocity = BALL_SPEED * dir;
  }
  void Update(sf::RenderTarget& window, float deltaTime, Player& player, Blocks& blocks) {
    sf::RectangleShape playerRect = player.GetRectangle();
    std::vector<std::vector<sf::RectangleShape>> blocksVec = blocks.GetBlocks();

    if (ball.getPosition().x <= 0 or ball.getPosition().x + BALL_SIZE >= window.getSize().x)
      velocity.x = -velocity.x;

    if (ball.getPosition().y <= 0)
      velocity.y = -velocity.y;

    if (ball.getPosition().y + BALL_SIZE >= window.getSize().y) {
      if (player.GetLives() > 0) {
        player.LoseLife();
      }
      ball.setPosition(originalPosition);
    }

    if (ball.getGlobalBounds().intersects(playerRect.getGlobalBounds()))
      velocity.y = -velocity.y;

    for (size_t row = 0; row < blocksVec.size(); row++) {
      for (size_t col = 0; col < blocksVec[row].size(); col++) {
        if (ball.getGlobalBounds().intersects(blocksVec[row][col].getGlobalBounds())) {
          blocks.RemoveBlock(row, col);
          velocity.y = -velocity.y;
        }
      }
    }
    ball.move(velocity * deltaTime);
  }

 private:
  sf::Vector2f originalPosition;
  sf::Vector2f velocity;
  sf::RectangleShape ball;
};
