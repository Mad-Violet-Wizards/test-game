#include <iostream>

#include "Window.hpp"

Window::Window(const std::string &windowName)
  : m_renderWindow(m_windowResolutionInfo.GetDefaultResolution(), windowName, sf::Style::Fullscreen)
{
  std::cout << "[Window] Created new Window.\n";
}

Window::~Window() {}

void Window::Update()
{
  sf::Event event;

  if (m_renderWindow.pollEvent(event))
  {
    EventHandler::GetInstance().ProcessEvent(event);

    if (event.type == sf::Event::Closed)
    {
      m_renderWindow.close();
    }
  }
}

void Window::BeginDraw()
{
  m_renderWindow.clear(sf::Color::Black);
}

void Window::Draw(const sf::Drawable &drawable)
{
  m_renderWindow.draw(drawable);
}

void Window::EndDraw()
{
  m_renderWindow.display();
}

bool Window::IsOpen() const
{
  return m_renderWindow.isOpen();
}

sf::RenderWindow* Window::GetWindow()
{
  return &m_renderWindow;
}

sf::Vector2u Window::GetWindowSize() const
{
  return m_renderWindow.getSize();
}

void Window::Exit()
{
  m_renderWindow.close();
}
