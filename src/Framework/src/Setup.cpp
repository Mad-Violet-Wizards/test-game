#include "Setup.hpp"

#include <iostream>

Setup::Setup()
{
  m_currentMode = 0;
  m_videoModes = sf::VideoMode::getFullscreenModes();
}

Setup::~Setup()
{

}

sf::VideoMode Setup::GetBestWindowSetup()
{
  return m_videoModes[0];
}

sf::VideoMode Setup::GetCurrentMode()
{
  return m_videoModes[m_currentMode];
}

void Setup::IncreaseMode()
{
  m_currentMode++;

  if (m_currentMode >= m_videoModes.size() - 1)
  {
    m_currentMode = 0;
  }
}

void Setup::DecreaseMode()
{
  m_currentMode--;

  if (m_currentMode <= 0)
  {
    m_currentMode = m_videoModes.size() - 1;
  }
}