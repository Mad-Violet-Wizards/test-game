#include <iostream>

#include "GuiTextWidget.hpp"
#include "Window.hpp"

GuiTextWidget::GuiTextWidget(Window* window)
  : GuiWidget(window)
{
  std::cout << "[GuiTextWidget] Creating new GuiTextWidget \n";

  if (!m_font.loadFromFile("../../src/Assets/Roboto-Black.ttf"))
  {
    std::cout << "[GuiTextWidget] Error while loading font.\n";
  }
  m_text.setFont(m_font);
}

GuiTextWidget::~GuiTextWidget()
{
  std::cout << "[GuiTextWidget] Destroyed GuiTextWidget \n";
}

void GuiTextWidget::Update()
{
  const sf::Vector2f mousePosition = static_cast<sf::Vector2f>(sf::Mouse::getPosition(*m_window -> GetWindow()));
  if (m_text.getGlobalBounds().contains(mousePosition))
  {
    // Invoke action here.
  }
}

void GuiTextWidget::SetCharacterSize(const int size)
{
  m_text.setCharacterSize(size);
}

void GuiTextWidget::SetString(const std::string& string)
{
  m_text.setString(string);
}

void GuiTextWidget::SetColor(const int r, const int g, const int b)
{
  m_text.setFillColor(sf::Color(r, g, b));
}

void GuiTextWidget::SetColor(const sf::Color& color)
{
  m_text.setFillColor(color);
}

void GuiTextWidget::SetAbsolutePosition(const sf::Vector2f& position)
{
  m_text.setPosition(position);
}

void GuiTextWidget::SetAbsolutePosition(float x, float y)
{
  m_text.setPosition(sf::Vector2f(x, y));
}

void GuiTextWidget::SetRelativePosition(const std::string& x, const std::string& y)
{
}

void GuiTextWidget::SetRelativePosition(const char* x, const char* y)
{
}

void GuiTextWidget::SetRelativePosition(const int x, const int y)
{
  const sf::Vector2u windowSize = m_window -> GetWindowSize();

  if (x > 100 || y > 100 || x < 0 || y < 0)
  {
    throw std::logic_error("[Error]: Relative position of widget must be <1, 100>");
  }
  else
  {
    const int textWidth = static_cast<int>(m_text.getLocalBounds().width / 2);
    const int textHeight = static_cast<int>(m_text.getLocalBounds().height / 2);

    const int xPosition = windowSize.x * x / 100 - textWidth;
    const int yPosition = windowSize.y * y / 100 - textHeight;
    m_text.setPosition(static_cast<float>(xPosition), static_cast<float>(yPosition));
  }
}

void GuiTextWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_text, states);
}
