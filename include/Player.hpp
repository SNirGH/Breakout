#pragma once

#include <SFML/Graphics.hpp>

constexpr float PLAYER_WIDTH = 64.0f;
constexpr float PLAYER_HEIGHT = 16.0f;
constexpr float PLAYER_SPEED = 200.0f;

class Player {
 public:
  Player(const sf::Vector2f& pos) {
    player.setSize({PLAYER_WIDTH, PLAYER_HEIGHT});
    player.setPosition(pos);
  }
  void Draw(sf::RenderTarget& rt) {
    rt.draw(player);
  }
  void Controls(float deltaTime) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
      player.move(-PLAYER_SPEED * deltaTime, 0);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
      player.move(PLAYER_SPEED * deltaTime, 0);
  }
  void Update(sf::RenderTarget& window) {
    sf::Vector2f playerPosition = player.getPosition();

    playerPosition.x = std::clamp(playerPosition.x, 0.0f, window.getSize().x - PLAYER_WIDTH);
    playerPosition.y = std::clamp(playerPosition.y, 0.0f, window.getSize().y - PLAYER_WIDTH);

    player.setPosition(playerPosition);
  }

  sf::RectangleShape GetRectangle() const { return player; }

  uint8_t GetLives() const { return lives; }
  void LoseLife() { --lives; }

 private:
  uint8_t lives = 3;
  sf::Vector2f velocity;
  sf::RectangleShape player;
};
