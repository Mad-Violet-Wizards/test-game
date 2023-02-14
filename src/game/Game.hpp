#pragma once

#include "SceneGame.hpp"
#include "SceneMenu.hpp"
#include "SceneLoading.hpp"

#include "SceneStateMachine.hpp"

class Game
{

public:

  Game();
  ~Game();

  void GameLoop();

  void Update();
  void LateUpdate();
  void Draw();
  void CalculateDeltaTime();
  bool IsRunning() const;

  void CreateLoadingScene();
  void CreateScenesAfterLoading();

private:

  Window m_window;
  SceneStateMachine m_sceneManager;

  sf::Clock m_clock;
  float m_deltaTime;
};
