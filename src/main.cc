#include <Ball.hpp>
#include <Blocks.hpp>

int main() {
  sf::RenderWindow window(sf::VideoMode(600, 900), "Breakout");
  sf::CircleShape circle;
  sf::Vector2f windowSize = static_cast<sf::Vector2f>(window.getSize());

  Blocks blocks;

  Player player({windowSize.x / 2, windowSize.y - 50.0f});
  Ball ball({300.0f, 300.0f});
  ball.SetDirection({1.0f, 1.0f});
  blocks.RemoveBlock(1, 1);

  sf::Clock clock;

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();

    float deltaTime = clock.restart().asSeconds();

    player.Controls(deltaTime);

    ball.Update(window, deltaTime, player);
    player.Update(window);

    window.clear();
    blocks.Draw(window);
    player.Draw(window);
    ball.Draw(window);
    window.display();
  }

  return 0;
}
