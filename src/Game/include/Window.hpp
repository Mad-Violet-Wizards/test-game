#pragma once

#include <SFML/Graphics.hpp>

#include "WindowResolution.hpp"

class Window
{
public:

  Window(const std::string &windowName);
  ~Window();

  void Update();
  void BeginDraw();
  void Draw(const sf::Drawable &drawable);
  void EndDraw();

  bool IsOpen() const;
  void Exit();

  sf::RenderWindow *GetWindow();
  sf::Vector2u GetWindowSize() const;

  sf::RenderWindow m_window;

private:

  WindowResolution m_windowResolutionInfo;

};
