#include <iostream>

#include "GuiLayout.hpp"

GuiLayout::GuiLayout() 
{
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

void GuiLayout::Draw(Window& window)
{
	for (auto& widget : m_widgets)
	{
		window.Draw(*static_cast<sf::Drawable*>(widget.get()));
	}
}