#pragma once

#include <SFML/Graphics.hpp>

class WindowResolution
{
public:

  WindowResolution();
  ~WindowResolution();

  sf::VideoMode GetDefaultResolution();
  sf::VideoMode GetCurrentResolution();

  const std::string GetCurrentResolutionString();

  void IncreaseMode();
  void DecreaseMode();

private:

  size_t m_currentMode;
  std::vector<sf::VideoMode> m_videoModes;
};