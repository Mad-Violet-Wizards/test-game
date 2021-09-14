#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GuiLayout.hpp"
#include "Window.hpp"

class GuiManager
{
	public:

		GuiManager();
		~GuiManager();

		void AddLayout(GuiLayout layout);
		void RemoveLayout();

		void Draw(Window& window);

	private:

		std::vector<GuiLayout> m_layouts;
};
