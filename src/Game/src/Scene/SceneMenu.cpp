#include <iostream>
#include <SFML/Graphics.hpp>

#include "Scene/SceneMenu.hpp"


SceneMenu::SceneMenu(Window* window) : m_window(window)
{
  m_menuLayout = std::make_shared<GuiLayout>(m_window);
  m_ButtonNewGame = std::make_shared<Button_NewGame>(m_window);
  m_ButtonLoadGame = std::make_shared<Button_LoadGame>(m_window);
  m_ButtonOptions = std::make_shared<Button_Options>(m_window);
  m_ButtonExit = std::make_shared<Button_Exit>(m_window);
  m_test = std::make_shared<GuiTextWidget>(m_window);

  m_menuLayout -> AddWidget(m_ButtonNewGame);
  m_menuLayout -> AddWidget(m_ButtonLoadGame);
  m_menuLayout -> AddWidget(m_ButtonOptions);
  m_menuLayout -> AddWidget(m_ButtonExit);

  m_menuGuiManager.AddLayout(GuiManager::LayoutLevel::Level1, m_menuLayout);
}

SceneMenu::~SceneMenu() {}

void SceneMenu::OnCreate()
{
	
}

void SceneMenu::OnDestroy()
{

}

void SceneMenu::Update(float deltaTime)
{
  m_menuGuiManager.Update();
}

void SceneMenu::Draw(Window& window)
{
	m_menuGuiManager.Draw(window);
}