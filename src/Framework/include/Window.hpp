#pragma once

#include <SFML/Graphics.hpp>

#include "WindowResolution.hpp"
#include "EventHandler.hpp"

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

private:

  WindowResolution m_windowResolutionInfo;

  // Issue with public member because of ambigous name.
  sf::RenderWindow m_renderWindow;

};
