#pragma once

#include <memory>

#include "Scene.hpp"
#include "Window.hpp"
#include "SceneStateMachine.hpp"
#include "GuiManager.hpp"
#include "GuiLayout.hpp"
#include "GuiLayoutVertical.hpp"
#include "GuiObject.hpp"
#include "GuiTextWidget.hpp"
#include "WindowResolution.hpp"

class SceneMenu : public Scene
{

public:

  SceneMenu(Window *window, SceneStateMachine *sceneManager);
  ~SceneMenu();

  void OnCreate() override;
  void OnDestroy() override;

  void Update(float deltaTime) override;
  void Draw(Window &window) override;

  //
  // Signal & Slots
  //

  void StartNewGame();
  void OpenOptions();
  void ExitGame();
  void EmptySlot();

  void ChangeWindowResolution();
  void CloseOptions();

  //
  // End of signal & slots section.
  //

private:

  void CreateGUI();
  void InitConnections();

private:

  Window *m_window;
  SceneStateMachine *m_sceneManager;
  WindowResolution m_windowResolutionInformations;

  GuiManager m_menuGuiManager;

  std::shared_ptr<GuiLayoutVertical> m_mainMenuLayout;
  std::shared_ptr<GuiTextWidget> m_buttonNewGame;
  std::shared_ptr<GuiTextWidget> m_buttonLoadGame;
  std::shared_ptr<GuiTextWidget> m_buttonOptions;
  std::shared_ptr<GuiTextWidget> m_buttonExit;

  std::shared_ptr<GuiLayoutVertical> m_optionsMenuLayout;
  std::shared_ptr<GuiTextWidget> m_resolutionInfo;
  std::shared_ptr<GuiTextWidget> m_buttonResolution;
  std::shared_ptr<GuiTextWidget> m_buttonCloseOptions;

};
