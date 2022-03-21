#include <iostream>

#include "GuiObject.hpp"
#include "Window.hpp"

GuiObject::GuiObject(Window* window)
  : m_window(window)
{
  std::cout << "[Info][GuiWidget]: Created new GuiWidget \n";
  m_position = sf::Vector2f{ 0.f, 0.f };
  m_margins.top = 12.f;
  m_margins.bottom = 4.f;
  m_margins.left = 4.f;
  m_margins.right = 12.f;
  m_align = GuiAlign::AlignCenter;
  //m_testRect.setSize(sf::Vector2f(200, 200));
  //m_testRect.setFillColor(sf::Color::Green);

  m_visible = true;

  m_mouseTracking = false;
}

GuiObject::~GuiObject()
{
  std::cout << "[Info][GuiWidget]: Destroyed GuiWidget \n";
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

void GuiObject::SetTopMargin(const float topMargin)
{
  m_margins.top = topMargin;
}

void GuiObject::SetRightMargin(const float rightMargin)
{
  m_margins.right = rightMargin;
}

void GuiObject::SetBottomMargin(const float bottomMargin)
{
  m_margins.bottom = bottomMargin;
}

void GuiObject::SetLeftMargin(const float leftMargin)
{
  m_margins.left = leftMargin;
}

void GuiObject::GetMargins(float &topMargin, float &rightMargin, float &bottomMargin, float &leftMargin)
{
  topMargin = m_margins.top;
  rightMargin = m_margins.right;
  bottomMargin = m_margins.bottom;
  leftMargin = m_margins.left;
}

GuiObject::GuiMargins GuiObject::GetMargins()
{
  return m_margins;
}

float GuiObject::GetTopMargin() const
{
  return m_margins.top;
}

float GuiObject::GetRightMargin() const
{
  return m_margins.right;
}

float GuiObject::GetBottomMargin() const
{
  return m_margins.bottom;
}

float GuiObject::GetLeftMargin() const
{
  return m_margins.left;
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
