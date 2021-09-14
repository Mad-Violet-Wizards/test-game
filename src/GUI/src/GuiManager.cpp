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

void GuiManager::AddLayout(GuiLayout layout) 
{
	m_layouts.push_back(layout);
}

void GuiManager::RemoveLayout() {}

void GuiManager::Draw(Window& window) 
{
	for (auto& layout : m_layouts)
	{
		layout.Draw(window);
	}
}