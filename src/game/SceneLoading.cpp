#include <iostream>

#include "SceneLoading.hpp"
#include "Game.hpp"
#include "File.hpp"

SceneLoading::SceneLoading(Window *window)
  : m_window(window)
{
}  

SceneLoading::~SceneLoading()
{
}

void SceneLoading::OnCreate()
{
  AssetsStorage::GetInstance().LoadFont("../assets/fonts/GoudyBookletter.ttf");
  CreateGUI();
}

void SceneLoading::OnDestroy()
{

}

void SceneLoading::Update(float deltaTime)
{
    m_guiManager.Update(deltaTime);
}

void SceneLoading::LateUpdate(float deltaTime)
{
}
  
void SceneLoading::Draw(Window &window)
{
  m_guiManager.Draw(window);
}

void SceneLoading::CreateGUI()
{
  m_loadingLayout = std::make_shared<GuiLayoutVertical>(m_window);
  m_loadingText = std::make_shared<GuiTextWidget>(m_window);
  m_loadingText -> SetColor(sf::Color::White);
  m_loadingText -> SetCharacterSize(24);
  m_loadingText -> SetText("~~ Loading --");
  m_loadingText -> SetAlign(GuiAlign::AlignCenter);

  m_loadingLayout -> SetRelativeSize(100, 0);
  m_loadingLayout -> SetRelativePosition(0, 25);
  m_loadingLayout -> AddWidget(m_loadingText);

  m_guiManager.AddLayout(GuiManager::LayoutLevel::Level1, m_loadingLayout);
}