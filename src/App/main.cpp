#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

#include "Game.hpp"
#include "Logs.hpp"

int main()
{
  Game game;

  while (game.IsRunning()) 
  {
    game.CaptureInput();
    game.Update();
    game.Draw();
    game.CalculateDeltaTime();
  }
}
