#include <iostream>
#include <SFML/Graphics.hpp>
#include <boost/bind/bind.hpp>

#include "GuiLayout.hpp"
#include "GuiAlign.hpp"
#include "SceneMenu.hpp"
#include "EventHandler.hpp"
#include "GuiImage.hpp"

SceneMenu::SceneMenu(Window *window, SceneStateMachine *sceneManager)
  : m_window(window),
    m_sceneManager(sceneManager)
{
  CreateGUI();
  InitConnections();
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
  m_menuGuiManager.Update(deltaTime);
}

void SceneMenu::Draw(Window &window)
{
  m_menuGuiManager.Draw(window);
}

void SceneMenu::StartNewGame()
{
  m_sceneManager -> SwitchTo(0);
}

void SceneMenu::OpenOptions()
{
  m_mainMenuLayout    -> SetVisible(false);
  m_optionsMenuLayout -> SetVisible(true);
}

void SceneMenu::ExitGame()
{
  m_window -> Exit();
}

void SceneMenu::EmptySlot()
{
  // Nothing here.
}

void SceneMenu::ChangeWindowResolution()
{
  m_windowResolutionInformations.IncreaseMode();
  m_window -> UpdateResolution(m_windowResolutionInformations.GetCurrentResolution());
  m_buttonResolution -> SetText(m_windowResolutionInformations.GetCurrentResolutionString());
}

void SceneMenu::CloseOptions()
{
  m_optionsMenuLayout -> SetVisible(false);
  m_mainMenuLayout    -> SetVisible(true);
}

void SceneMenu::CreateGUI()
{
  m_mainMenuLayout = std::make_shared<GuiLayoutVertical>(m_window);
  m_buttonNewGame = std::make_shared<GuiTextWidget>(m_window);
  m_buttonNewGame -> SetColor(sf::Color::White);
  m_buttonNewGame -> SetCharacterSize(24);
  m_buttonNewGame -> SetText("New Game");
  m_buttonNewGame -> SetMouseTracking(true);

  m_buttonLoadGame = std::make_shared<GuiTextWidget>(m_window);
  m_buttonLoadGame -> SetColor(sf::Color::White);
  m_buttonLoadGame -> SetCharacterSize(24);
  m_buttonLoadGame -> SetText("Load Game");
  m_buttonLoadGame -> SetAlign(GuiAlign::AlignCenter);

  m_buttonOptions = std::make_shared<GuiTextWidget>(m_window);
  m_buttonOptions -> SetColor(sf::Color::White);
  m_buttonOptions -> SetCharacterSize(24);
  m_buttonOptions -> SetText("Options");
  m_buttonOptions -> SetAlign(GuiAlign::AlignCenter);
  m_buttonOptions -> SetMouseTracking(true);

  m_buttonExit = std::make_shared<GuiTextWidget>(m_window);
  m_buttonExit -> SetColor(sf::Color::White);
  m_buttonExit -> SetCharacterSize(24);
  m_buttonExit -> SetText("Exit");
  m_buttonExit -> SetAlign(GuiAlign::AlignCenter);
  m_buttonExit -> SetMouseTracking(true);

  m_mainMenuLayout -> SetRelativeSize(100, 0);
  m_mainMenuLayout -> SetRelativePosition(0, 25);
  m_mainMenuLayout -> AddWidget(m_buttonNewGame);
  m_mainMenuLayout -> AddWidget(m_buttonLoadGame);
  m_mainMenuLayout -> AddWidget(m_buttonOptions);
  m_mainMenuLayout -> AddWidget(m_buttonExit);

  m_optionsMenuLayout = std::make_shared<GuiLayoutVertical>(m_window);
  m_resolutionInfo = std::make_shared<GuiTextWidget>(m_window);
  m_resolutionInfo -> SetColor(sf::Color::White);
  m_resolutionInfo -> SetCharacterSize(24);
  m_resolutionInfo -> SetText("Current Resolution:");
  m_resolutionInfo -> SetAlign(GuiAlign::AlignCenter);

  m_buttonResolution = std::make_shared<GuiTextWidget>(m_window);
  m_buttonResolution -> SetColor(sf::Color::White);
  m_buttonResolution -> SetCharacterSize(24);

  m_buttonResolution -> SetText(m_windowResolutionInformations.GetCurrentResolutionString());
  m_buttonResolution -> SetAlign(GuiAlign::AlignCenter);
  m_buttonResolution -> SetMouseTracking(true);

  m_buttonCloseOptions = std::make_shared<GuiTextWidget>(m_window);
  m_buttonCloseOptions -> SetColor(sf::Color::White);
  m_buttonCloseOptions -> SetCharacterSize(24);
  m_buttonCloseOptions -> SetText("Close Options");
  m_buttonCloseOptions -> SetAlign(GuiAlign::AlignCenter);
  m_buttonCloseOptions -> SetMouseTracking(true);

  m_optionsMenuLayout -> SetRelativeSize(100, 0);
  m_optionsMenuLayout -> SetRelativePosition(0, 25);
  m_optionsMenuLayout -> AddWidget(m_resolutionInfo);
  m_optionsMenuLayout -> AddWidget(m_buttonResolution);
  m_optionsMenuLayout -> AddWidget(m_buttonCloseOptions);
  m_optionsMenuLayout -> SetVisible(false);

  m_menuGuiManager.AddLayout(GuiManager::LayoutLevel::Level1, m_mainMenuLayout);
  m_menuGuiManager.AddLayout(GuiManager::LayoutLevel::Level2, m_optionsMenuLayout);
}

void SceneMenu::InitConnections()
{
  m_buttonNewGame  -> Clicked.connect(boost::bind(&SceneMenu::StartNewGame, this));
  m_buttonLoadGame -> Clicked.connect(boost::bind(&SceneMenu::EmptySlot, this));
  m_buttonOptions  -> Clicked.connect(boost::bind(&SceneMenu::OpenOptions, this));
  m_buttonExit     -> Clicked.connect(boost::bind(&SceneMenu::ExitGame, this));

  m_buttonResolution   -> Clicked.connect(boost::bind(&SceneMenu::ChangeWindowResolution, this));
  m_buttonCloseOptions -> Clicked.connect(boost::bind(&SceneMenu::CloseOptions, this));

  m_window -> ResolutionChanged.connect(boost::bind(&GuiLayoutVertical::RefreshSize,
                                                    m_mainMenuLayout));

  m_window -> ResolutionChanged.connect(boost::bind(&GuiLayoutVertical::RefreshSize,
                                                    m_optionsMenuLayout));
}