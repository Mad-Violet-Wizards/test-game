#include <iostream>
#include <SFML/Graphics.hpp>

#include "Scene/SceneMenu.hpp"


SceneMenu::SceneMenu() 
{
  m_menuLayout = std::make_shared<GuiLayout>();
  m_testLayout = std::make_shared<GuiLayout>();
  m_test1 = std::make_shared<GuiWidget>();
  m_textWidget = std::make_shared<GuiTextWidget>();
  
  m_textWidget -> SetString(std::string{"New Game"});
  m_textWidget -> SetPosition(50, 50);
  m_menuLayout -> AddWidget(m_textWidget);

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
  m_menuGuiManager.Update();
}

void SceneMenu::Draw(Window& window)
{
	m_menuGuiManager.Draw(window);
}