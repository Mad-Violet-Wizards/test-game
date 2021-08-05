#include <iostream>
#include <string>
#include <unistd.h>

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
