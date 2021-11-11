#include <iostream>

#include "GuiManager.hpp"

GuiManager::GuiManager() 
{
  std::cout << "[Gui Manager] Created new Gui Manager\n";
}

GuiManager::~GuiManager() 
{
  std::cout << "[Gui Manager] Destroyed Gui Manager \n";
}

void GuiManager::AddLayout(LayoutLevel level, std::shared_ptr<GuiLayout> layout) 
{
  for (const std::pair<LayoutLevel, std::shared_ptr<GuiLayout>>& layout : m_layouts)
  {
    if (layout.first == level)
    {
      throw std::logic_error("[Error] Layout Level is already occupied.\n");
    }
  }
  m_layouts.push_back(std::make_pair(level, layout));
}

void GuiManager::RemoveLayout() {}

void GuiManager::Update()
{
  for (auto& layout : m_layouts)
  {
    layout.second -> Update();
  }
}

void GuiManager::Draw(Window& window) 
{
  for (auto& layout : m_layouts)
  {
	   layout.second -> Draw(window);
	 }
}