#include "Debug.hpp"

std::vector<sf::RectangleShape> Debug::m_rects;

void Debug::Draw(Window &window)
{
  for (auto &rect : m_rects)
  {
    window.Draw(rect);
  }

  m_rects.clear();
}

void Debug::AddRect(const sf::FloatRect &rect, sf::Color color)
{
  sf::RectangleShape shape;
  shape.setPosition(rect.left, rect.top);
  shape.setSize({ rect.width, rect.height });
  shape.setFillColor(sf::Color::Transparent);
  shape.setOutlineColor(color);
  shape.setOutlineThickness(2.0f);

  m_rects.push_back(shape);
}