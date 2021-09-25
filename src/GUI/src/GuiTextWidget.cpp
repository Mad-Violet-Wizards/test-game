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

void GuiTextWidget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_text, states);
}
