#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Game.hpp"

int main()
{
  Game game;

  while (game.IsRunning())
  {
    game.Update();
    game.LateUpdate();
    game.Draw();
    game.CalculateDeltaTime();
  }
}
