#include "Game.hpp"

Game::Game() : m_window("Test-Game 1.0.0")
{
  m_deltaTime = m_clock.restart().asSeconds();

  std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>();

  unsigned int gameSceneID = m_sceneManager.Add(gameScene);

  m_sceneManager.SwitchTo(gameSceneID);

  m_deltaTime = m_clock.restart().asSeconds();

}

Game::~Game() {}

void Game::CaptureInput()
{
  m_sceneManager.ProcessInput();
}

void Game::Update()
{
  m_window.Update();

  m_sceneManager.Update(m_deltaTime);
}

void Game::Draw()
{
  m_window.BeginDraw();
  m_sceneManager.Draw(m_window);
  m_window.EndDraw();
}

void Game::CalculateDeltaTime()
{
  m_deltaTime = m_clock.restart().asSeconds();
}

bool Game::IsRunning() const
{
  return m_window.IsOpen();
}
