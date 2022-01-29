#pragma once

#include <SFML/Graphics.hpp>
#include <list>
#include <memory>

#include "GuiLayout.hpp"
#include "Window.hpp"

class GuiManager
{
public:

  enum class LayoutLevel
  {
    Level1,
    Level2,
    Level3,
    Level4,
    Level5
  };

  GuiManager();
  ~GuiManager();

  void AddLayout(LayoutLevel level, std::shared_ptr<GuiLayout> layout);
  void RemoveLayout(std::shared_ptr<GuiLayout> layout);

  void UpdateLayoutLevel(LayoutLevel level, std::shared_ptr<GuiLayout> layout);

  void Update();
  void Draw(Window& window);

private:

  std::list<std::pair<LayoutLevel, std::shared_ptr<GuiLayout>>> m_layouts;
};
