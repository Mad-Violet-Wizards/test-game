#include "Game.hpp"
#include "FpsCounter.hpp"

Game::Game() : m_window("Test-Game 1.0.0")
{
  std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>();
  std::shared_ptr<SceneMenu> menuScene = std::make_shared<SceneMenu>(&m_window, &m_sceneManager);

  unsigned int gameSceneID = m_sceneManager.Add(gameScene);
  unsigned int menuSceneID = m_sceneManager.Add(menuScene);

  m_sceneManager.SwitchTo(menuSceneID);

  m_deltaTime = m_clock.restart().asSeconds();

}

Game::~Game() {}

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

  FpsCounter::GetInstance().CalculateFramesPerSecond(m_deltaTime);
}

bool Game::IsRunning() const
{
  return m_window.IsOpen();
}
