#include "Game.hpp"
#include "FpsCounter.hpp"
#include "AssetsStorage.hpp"
#include "ProjectileStorage.hpp"

#include <future>
#include <thread>
#include <chrono>

Game::Game() : m_window("Test-Game 1.0.0")
{
  std::shared_ptr<SceneLoading> loadingScene = std::make_shared<SceneLoading>(&m_window);
  unsigned int loadingSceneID = m_sceneManager.Add(loadingScene);
  m_sceneManager.SwitchTo(loadingSceneID);

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
}

bool Game::IsRunning() const
{
  return m_window.IsOpen();
}

void Game::CreateScenesAfterLoading()
{
  std::shared_ptr<SceneGame> gameScene = std::make_shared<SceneGame>();
  std::shared_ptr<SceneMenu> menuScene = std::make_shared<SceneMenu>(&m_window, &m_sceneManager);

  unsigned int gameSceneID = m_sceneManager.Add(gameScene);
  unsigned int menuSceneID = m_sceneManager.Add(menuScene);
  m_sceneManager.SwitchTo(menuSceneID);
}

void Game::LoadAssets()
{
  ProjectileStorage::Initalize();

  if (AssetsStorage::GetInstance().ParseAssetsSchema("../assets/assets-schema.json"))
  {
    CreateScenesAfterLoading();
  }
}