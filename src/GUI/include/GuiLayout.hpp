#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "GuiWidget.hpp"
#include "Window.hpp"

class GuiLayout
{
	public:
		
		GuiLayout(Window* window);
		~GuiLayout();

		void AddWidget(std::shared_ptr<GuiWidget> widget);
		void RemoveWidget();

  void SetVisible(bool state);
  void SetSize(const unsigned int x, const unsigned int y);
  void SetSize(const sf::Vector2u& size);

  void Update();
		void Draw(Window& window);

	private:

		std::vector<std::shared_ptr<GuiWidget>> m_widgets;
  Window* m_window;
  sf::Vector2u m_size;
  bool m_isVisible;
};
