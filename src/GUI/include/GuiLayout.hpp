#pragma once

#include <SFML/Graphics.hpp>

#include "Window.hpp"

class GuiLayout
{
	public:
		
		GuiLayout();
		~GuiLayout();

		void AddWidget(sf::RectangleShape widget);
		void RemoveWidget();

		void Draw(Window& window);

	private:

		std::vector<sf::RectangleShape> m_widgets;
};
