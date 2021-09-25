#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GuiLayout.hpp"
#include "Window.hpp"

class GuiManager
{
	public:

		GuiManager();
		~GuiManager();

		void AddLayout(std::shared_ptr<GuiLayout> layout);
		void RemoveLayout();

		void Draw(Window& window);

	private:

		std::vector<std::shared_ptr<GuiLayout>> m_layouts;
};
