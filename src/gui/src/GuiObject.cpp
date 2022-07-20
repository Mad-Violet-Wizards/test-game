#include <iostream>

#include "GuiObject.hpp"

GuiObject::GuiObject(Window* window)
  : m_window(window)
{
  m_position = sf::Vector2f{ 0.f, 0.f };
  m_align = GuiAlign::AlignCenter;

  m_visible = true;

  m_mouseTracking = false;
}

GuiObject::~GuiObject()
{
}

void GuiObject::SetPosition(const float x, const float y)
{
  m_position = sf::Vector2f { x, y };
}
  
void GuiObject::SetPosition(const sf::Vector2f &position)
{
  m_position = position;
}

const sf::Vector2f &GuiObject::GetPosition()
{
  return m_position;
}

GuiMargin &GuiObject::GetMargin()
{
  return m_margins;
}

void GuiObject::SetAlign(GuiAlign align)
{
  m_align = align;
}

GuiObject::GuiAlign GuiObject::GetAlign()
{
  return m_align;
}

void GuiObject::SetVisible(bool visible)
{
  m_visible = visible;
}

void GuiObject::SetMouseTracking(bool mouseTracking)
{
  m_mouseTracking = mouseTracking;
}

void GuiObject::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_testRect, states);
}
