#include <iostream>

#include "GuiWidget.hpp"

GuiWidget::GuiWidget()
{
  std::cout << "[GuiWidget] Created new GuiWidget \n";
  m_testRect.setSize(sf::Vector2f(200, 200));
  m_testRect.setFillColor(sf::Color::Green);
}

GuiWidget::~GuiWidget()
{
  std::cout << "[GuiWidget] Destroyed GuiWidget \n";
}

void GuiWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_testRect, states);
}
