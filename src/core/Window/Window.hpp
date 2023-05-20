#pragma once

#include "WindowResolution.hpp"
#include "Events/EventHandler.hpp"

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
  void UpdateResolution(const sf::VideoMode &videMode);

  //
  // Signal & Slots
  //

  boost::signals2::signal<void()> ResolutionChanged;

private:

  WindowResolution m_windowResolutionInfo;

  // Issue with public member because of ambigous name.
  sf::RenderWindow m_renderWindow;

};
