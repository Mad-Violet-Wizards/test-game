#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
  Game game;

  sf::Thread LoadingThread(&Game::LoadAssets, &game);

  LoadingThread.launch();

  while (game.IsRunning())
  {
    game.GameLoop();
  }

  return EXIT_SUCCESS;
}
