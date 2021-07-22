#include "Game.hpp"

Game::Game() : m_window("Onyx TEST 1.0.0")
{
  m_deltaTime = m_clock.restart().asSeconds();
}

Game::~Game() {}

void Game::Update()
{
  m_window.Update();
}

void Game::Draw()
{
  m_window.BeginDraw();
  m_window.EndDraw();
}

void Game::Draw(const sf::Drawable& drawable)
{
  m_window.BeginDraw();
  m_window.Draw(drawable);
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
