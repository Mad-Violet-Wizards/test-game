#pragma once

#include <SFML/Graphics.hpp>

class WindowResolution
{

public:

  WindowResolution();
  ~WindowResolution();

  const sf::VideoMode &GetDefaultResolution();
  const sf::VideoMode &GetCurrentResolution();

  const std::string GetCurrentResolutionString();

  void IncreaseMode();
  void DecreaseMode();

private:

  size_t m_currentMode;
  std::vector<sf::VideoMode> m_videoModes;

};
