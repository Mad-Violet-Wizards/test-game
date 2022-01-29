#include <iostream>
#include <SFML/Graphics.hpp>

#include "Scene/SceneMenu.hpp"


SceneMenu::SceneMenu(Window* window) : m_window(window)
{
  m_menuLayout = std::make_shared<GuiLayout>(m_window);
  m_testVerticalLayout = std::make_shared<GuiLayoutVertical>(m_window);
  m_test = std::make_shared<GuiTextWidget>(m_window);
  m_test -> SetColor(sf::Color::White);
  m_test -> SetCharacterSize(24);
  m_test -> SetText("New Game");

  m_test1 = std::make_shared<GuiTextWidget>(m_window);
  m_test1 -> SetColor(sf::Color::White);
  m_test1 -> SetCharacterSize(24);
  m_test1 -> SetText("Load Game");
  m_test1 -> SetAlign(GuiObject::GuiAlign::AlignCenter);

  m_test2 = std::make_shared<GuiTextWidget>(m_window);
  m_test2 -> SetColor(sf::Color::White);
  m_test2 -> SetCharacterSize(24);
  m_test2 -> SetText("Options");
  m_test2 -> SetAlign(GuiObject::GuiAlign::AlignCenter);

  m_test3 = std::make_shared<GuiTextWidget>(m_window);
  m_test3 -> SetColor(sf::Color::White);
  m_test3 -> SetCharacterSize(24);
  m_test3 -> SetText("Exit");
  m_test3 -> SetAlign(GuiObject::GuiAlign::AlignCenter);

  m_testVerticalLayout->SetRelativeSize(100, 0);
  m_testVerticalLayout->SetRelativePosition(0, 25);
  m_testVerticalLayout->AddWidget(m_test);
  m_testVerticalLayout->AddWidget(m_test1);
  m_testVerticalLayout->AddWidget(m_test2);
  m_testVerticalLayout->AddWidget(m_test3);

  m_testHorizontalLayout = std::make_shared<GuiLayoutHorizontal>(m_window);
  m_testH = std::make_shared<GuiTextWidget>(m_window);
  m_testH -> SetColor(sf::Color::White);
  m_testH -> SetCharacterSize(24);
  m_testH -> SetText("Exit");
  m_testH -> SetAlign(GuiObject::GuiAlign::AlignTop);

  m_testH1 = std::make_shared<GuiTextWidget>(m_window);
  m_testH1 -> SetColor(sf::Color::White);
  m_testH1 -> SetCharacterSize(24);
  m_testH1 -> SetText("Load Game");
  m_testH1 -> SetAlign(GuiObject::GuiAlign::AlignCenter);

  m_testH2 = std::make_shared<GuiTextWidget>(m_window);
  m_testH2 -> SetColor(sf::Color::White);
  m_testH2 -> SetCharacterSize(24);
  m_testH2 -> SetText("Options");
  m_testH2 -> SetAlign(GuiObject::GuiAlign::AlignBottom);

  m_testH3 = std::make_shared<GuiTextWidget>(m_window);
  m_testH3 -> SetColor(sf::Color::White);
  m_testH3 -> SetCharacterSize(24);
  m_testH3 -> SetText("New Game");
  m_testH3 -> SetAlign(GuiObject::GuiAlign::AlignTop);

  m_testHorizontalLayout -> SetRelativeSize(100, 25);
  m_testHorizontalLayout -> SetRelativePosition(0, 60);
  m_testHorizontalLayout->AddWidget(m_testH);
  m_testHorizontalLayout->AddWidget(m_testH1);
  m_testHorizontalLayout->AddWidget(m_testH2);
  m_testHorizontalLayout->AddWidget(m_testH3);

  m_menuGuiManager.AddLayout(GuiManager::LayoutLevel::Level1, m_testVerticalLayout);
  m_menuGuiManager.AddLayout(GuiManager::LayoutLevel::Level2, m_testHorizontalLayout);
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