#include <iostream>
#include <SFML/Graphics.hpp>
#include <boost/bind/bind.hpp>

#include "Scene/SceneMenu.hpp"


SceneMenu::SceneMenu(Window* window) : m_window(window)
{
  m_menuLayout = std::make_shared<GuiLayout>(m_window);
  m_testVerticalLayout = std::make_shared<GuiLayoutVertical>(m_window);
  m_buttonNewGame = std::make_shared<GuiTextWidget>(m_window);
  m_buttonNewGame -> SetColor(sf::Color::White);
  m_buttonNewGame -> SetCharacterSize(24);
  m_buttonNewGame -> SetText("New Game");
  m_buttonNewGame -> SetInput(&m_input);

  m_buttonLoadGame = std::make_shared<GuiTextWidget>(m_window);
  m_buttonLoadGame -> SetColor(sf::Color::White);
  m_buttonLoadGame -> SetCharacterSize(24);
  m_buttonLoadGame -> SetText("Load Game");
  m_buttonLoadGame -> SetAlign(GuiObject::GuiAlign::AlignCenter);
  m_buttonLoadGame -> SetInput(&m_input);

  m_buttonOptions = std::make_shared<GuiTextWidget>(m_window);
  m_buttonOptions -> SetColor(sf::Color::White);
  m_buttonOptions -> SetCharacterSize(24);
  m_buttonOptions -> SetText("Options");
  m_buttonOptions -> SetAlign(GuiObject::GuiAlign::AlignCenter);
  m_buttonOptions -> SetInput(&m_input);

  m_buttonExit = std::make_shared<GuiTextWidget>(m_window);
  m_buttonExit -> SetColor(sf::Color::White);
  m_buttonExit -> SetCharacterSize(24);
  m_buttonExit -> SetText("Exit");
  m_buttonExit -> SetAlign(GuiObject::GuiAlign::AlignCenter);
  m_buttonExit -> SetInput(&m_input);

  m_testVerticalLayout -> SetRelativeSize(100, 0);
  m_testVerticalLayout -> SetRelativePosition(0, 25);
  m_testVerticalLayout -> AddWidget(m_buttonNewGame);
  m_testVerticalLayout -> AddWidget(m_buttonLoadGame);
  m_testVerticalLayout -> AddWidget(m_buttonOptions);
  m_testVerticalLayout -> AddWidget(m_buttonExit);

  m_menuGuiManager.AddLayout(GuiManager::LayoutLevel::Level1, m_testVerticalLayout);

  InitConnections();
}

SceneMenu::~SceneMenu() {}

void SceneMenu::OnCreate()
{

}

void SceneMenu::OnDestroy()
{

}

void SceneMenu::ProcessInput()
{
  m_input.Update();
}

void SceneMenu::Update(float deltaTime)
{
  m_menuGuiManager.Update();
}

void SceneMenu::Draw(Window& window)
{
  m_menuGuiManager.Draw(window);
}

void SceneMenu::Test()
{
  std::cout << "Recived event from some button.\n";
}

void SceneMenu::InitConnections()
{
  m_buttonNewGame -> Clicked.connect(boost::bind(&SceneMenu::Test, this));
}