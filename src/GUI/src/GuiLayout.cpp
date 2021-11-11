#include <iostream>

#include "GuiLayout.hpp"

GuiLayout::GuiLayout(Window* window) : m_window(window), m_isVisible(true)
{ 
  m_size = m_window -> GetWindowSize();
  std::cout << "[Gui Layout] Created new Gui Layout\n";
}

GuiLayout::~GuiLayout()
{
	std::cout << "[Gui Layout] Destroyed Gui Layout\n";
}

void GuiLayout::AddWidget(std::shared_ptr<GuiWidget> widget)
{
	 m_widgets.push_back(widget);
}

void GuiLayout::RemoveWidget()
{

}

void GuiLayout::SetVisible(bool state)
{
  m_isVisible = state;
}

void GuiLayout::SetSize(const unsigned int x, const unsigned int y)
{
  m_size = sf::Vector2u{ x, y };
}

void GuiLayout::SetSize(const sf::Vector2u& size)
{
  m_size = size;
}


void GuiLayout::Update()
{
  for (auto& widget : m_widgets)
  {
    if (m_isVisible)
    {
      widget -> Update();
    }
  }
}

void GuiLayout::Draw(Window& window)
{
  for (auto& widget : m_widgets)
  {
    if (m_isVisible)
    {
      window.Draw(*static_cast<sf::Drawable*>(widget.get()));
    }
	}
}