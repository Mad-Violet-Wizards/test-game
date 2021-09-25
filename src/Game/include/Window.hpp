#pragma once

#include <SFML/Graphics.hpp>

class Window
{
  public:

      Window(const std::string& windowName);
      ~Window();

      void Update();
      void BeginDraw();
      void Draw(const sf::Drawable& drawable);
      void EndDraw();

      bool IsOpen() const;
      void Exit();

      static sf::Vector2u GetWindowSize();

  private:
  
    sf::RenderWindow m_window;
};
