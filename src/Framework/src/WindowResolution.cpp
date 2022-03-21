#include <string>
#include <boost/format.hpp>

#include "WindowResolution.hpp"

WindowResolution::WindowResolution()
{
  m_currentMode = 0;
  m_videoModes = sf::VideoMode::getFullscreenModes();
}

WindowResolution::~WindowResolution()
{

}

sf::VideoMode WindowResolution::GetDefaultResolution()
{
  return m_videoModes[0];
}

sf::VideoMode WindowResolution::GetCurrentResolution()
{
  return m_videoModes[m_currentMode];
}

const std::string WindowResolution::GetCurrentResolutionString()
{
  boost::format fmt = boost::format("%1% x %2%") 
                      % GetCurrentResolution().width 
                      % GetCurrentResolution().height;

  const std::string currentResolution = boost::str(fmt);

  return currentResolution;
}

void WindowResolution::IncreaseMode()
{
  m_currentMode++;

  if (m_currentMode >= m_videoModes.size() - 1)
  {
    m_currentMode = 0;
  }
}

void WindowResolution::DecreaseMode()
{
  m_currentMode--;

  if (m_currentMode <= 0)
  {
    m_currentMode = m_videoModes.size() - 1;
  }
}