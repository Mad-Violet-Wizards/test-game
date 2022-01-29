#pragma once

#include <SFML/Graphics.hpp>

class Setup
{
public:

  Setup();
  ~Setup();

  sf::VideoMode GetBestWindowSetup();
  sf::VideoMode GetCurrentMode();

  void IncreaseMode();
  void DecreaseMode();

private:

  int m_currentMode;
  std::vector<sf::VideoMode> m_videoModes;
};