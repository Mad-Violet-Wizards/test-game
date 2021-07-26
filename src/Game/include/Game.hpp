#pragma once

#include "Window.hpp"

class Game
{
  public:

      Game();
      ~Game();

      void Update();
      void Draw();
      void Draw(const sf::Drawable& drawable);
      void CalculateDeltaTime();
      bool IsRunning() const;

  private:

      Window m_window;

      sf::Clock m_clock;
      float m_deltaTime;

};
