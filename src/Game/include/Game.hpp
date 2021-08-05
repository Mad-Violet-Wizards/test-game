#pragma once

#include "Window.hpp"
#include "Scene/SceneStateMachine.hpp"
#include "Scene/SceneGame.hpp"

class Game
{
  public:

      Game();
      ~Game();

      void Update();
      void Draw();
      void CalculateDeltaTime();
      bool IsRunning() const;

  private:

      Window m_window;
      SceneStateMachine m_sceneManager;

      sf::Clock m_clock;
      float m_deltaTime;

};
