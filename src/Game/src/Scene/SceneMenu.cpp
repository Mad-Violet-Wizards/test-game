#include <iostream>
#include <SFML/Graphics.hpp>

#include "Scene/SceneMenu.hpp"


SceneMenu::SceneMenu() 
{
  m_menuLayout = std::make_shared<GuiLayout>();
  m_testLayout = std::make_shared<GuiLayout>();
  m_test1 = std::make_shared<GuiWidget>();
  
  m_menuLayout -> AddWidget(m_test1);

  m_menuGuiManager.AddLayout(m_menuLayout);
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

}

void SceneMenu::Draw(Window& window)
{
	m_menuGuiManager.Draw(window);
}