#include <iostream>

#include "GuiManager.hpp"
#include "Log.hpp"

GuiManager::GuiManager()
{
}

GuiManager::~GuiManager()
{
}

void GuiManager::AddLayout(LayoutLevel level, std::shared_ptr<GuiLayout> layout)
{
  for (const std::pair<LayoutLevel, std::shared_ptr<GuiLayout>> &layout : m_layouts)
  {
    if (layout.first == level)
    {
      LOG_ERROR("[GuiManager][AddLayout] Layout Level is already occupied.\n");
    }
  }
  m_layouts.push_back(std::make_pair(level, layout));
}

void GuiManager::RemoveLayout(std::shared_ptr<GuiLayout> layout)
{
  for (const std::pair<LayoutLevel, std::shared_ptr<GuiLayout>> &l : m_layouts)
  {
    if (l.second == layout)
    {
      m_layouts.remove(l);
      break;
    }
  }
}

void GuiManager::UpdateLayoutLevel(LayoutLevel level, std::shared_ptr<GuiLayout> layout)
{
  RemoveLayout(layout);

  for (const std::pair<LayoutLevel, std::shared_ptr<GuiLayout>> &l : m_layouts)
  {
    if (l.first == level)
    {
      LOG_INFO("[GuiManager][UpdateLayoutLevel] Layout level is already occupied, removing.");
      RemoveLayout(l.second);

      AddLayout(level, layout);
    }
  }
}

void GuiManager::Update(float deltaTime)
{
  for (auto &layout : m_layouts)
  {
    layout.second -> Update(deltaTime);
  }
}

void GuiManager::Draw(Window &window)
{
  for (auto &layout : m_layouts)
  {
    layout.second -> Draw(window);
  }
}
