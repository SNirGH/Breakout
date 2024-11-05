#pragma once

#include <Player.hpp>

constexpr float BALL_SIZE = 16.0f;
constexpr float BALL_SPEED = 100.0f;

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
  void Update(sf::RenderTarget& window, float deltaTime, Player& player) {
    sf::RectangleShape playerRect = player.GetRectangle();

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

    ball.move(velocity * deltaTime);
  }

 private:
  sf::Vector2f originalPosition;
  sf::Vector2f velocity;
  sf::RectangleShape ball;
};
