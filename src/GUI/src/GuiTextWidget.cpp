#include <iostream>

#include "GuiTextWidget.hpp"

GuiTextWidget::GuiTextWidget()
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
  std::cout << "[GuiTextWidget] Update\n";
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

void GuiTextWidget::SetPosition(const sf::Vector2f& position)
{
  m_text.setPosition(position);
}

void GuiTextWidget::SetPosition(float x, float y)
{
  m_text.setPosition(sf::Vector2f(x, y));
}

void GuiTextWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_text, states);
}
