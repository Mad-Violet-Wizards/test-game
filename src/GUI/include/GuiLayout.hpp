#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GuiWidget.hpp"
#include "Window.hpp"

class GuiLayout
{
	public:
		
		GuiLayout();
		~GuiLayout();

		void AddWidget(std::shared_ptr<GuiWidget> widget);
		void RemoveWidget();

    void Update();
		void Draw(Window& window);

	private:

		std::vector<std::shared_ptr<GuiWidget>> m_widgets;
};
