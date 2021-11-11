#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "GuiLayout.hpp"
#include "Window.hpp"

class GuiManager
{
	public:

    enum class LayoutFloor
    {
      Level1,
      Level2,
      Level3,
      Level4,
      Level5
    };

   using LayoutLevel = LayoutFloor;

		GuiManager();
		~GuiManager();

		void AddLayout(LayoutLevel level, std::shared_ptr<GuiLayout> layout);
		void RemoveLayout();

  void Update();
		void Draw(Window& window);

  private:

		  std::vector<std::pair<LayoutLevel, std::shared_ptr<GuiLayout>>> m_layouts;
};
