#include "Game.hpp"
#include "FpsCounter.hpp"
#include "ProjectileStorage.hpp"

Game::Game() : m_window("Test-Game 1.0.0")
{
  m_deltaTime = m_clock.restart().asSeconds();
}

void Game::GameLoop()
{
  Update();
  LateUpdate();
  Draw();
  CalculateDeltaTime();
}

Game::~Game() {}

void Game::Update()
{
  m_window.Update();

  m_sceneManager.Update(m_deltaTime);
}

void Game::LateUpdate()
{
  m_sceneManager.LateUpdate(m_deltaTime);
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

  if (FpsCounter::GetInstance().GetFps() < 60)
  {
    // CONSOLE_LOG_WARNING("[Game] Reporting that fps have dropped below 60.");
  }
}

bool Game::IsRunning() const
{
  return m_window.IsOpen();
}

void Game::CreateLoadingScene()
{
  std::shared_ptr<SceneLoading> loadingScene = std::make_shared<SceneLoading>(&m_window);

  unsigned int loadingSceneID = m_sceneManager.Add(loadingScene);

  m_sceneManager.SwitchTo(loadingSceneID);
}

void Game::CreateScenesAfterLoading()
{
  std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>();
  std::shared_ptr<SceneMenu> menuScene = std::make_shared<SceneMenu>(&m_window, &m_sceneManager);

  unsigned int gameSceneID = m_sceneManager.Add(gameScene);
  unsigned int menuSceneID = m_sceneManager.Add(menuScene);
  m_sceneManager.SwitchTo(menuSceneID);
}
