#include <iostream>
#include <string>
#include <unistd.h>

#include "Game.hpp"
#include "Logs.hpp"

int main()
{
  Game game;
  sf::CircleShape shape(100.f);
  shape.setFillColor(sf::Color::Green);

  while (game.IsRunning()) 
  {
    game.Update();
    game.Draw(shape);
    game.CalculateDeltaTime();
  }
}
