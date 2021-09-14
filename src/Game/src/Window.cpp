#include "Window.hpp"

Window::Window(const std::string& windowName)
	: m_window(sf::VideoMode(800, 600, 32), windowName) 
{}

Window::~Window() {}

void Window::Update()
{
  sf::Event event;

  if (m_window.pollEvent(event))
  {
    if  (event.type == sf::Event::Closed)
    {
      m_window.close();
    }
  }
}

void Window::BeginDraw()
{
  m_window.clear(sf::Color::Black);
}

void Window::Draw(const sf::Drawable& drawable)
{
  m_window.draw(drawable);
}

void Window::EndDraw()
{
  m_window.display();
}

bool Window::IsOpen() const
{
  return m_window.isOpen();
}

void Window::Exit()
{
  m_window.close();
}
