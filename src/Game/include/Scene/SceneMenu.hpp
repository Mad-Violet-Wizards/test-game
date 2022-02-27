#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "Window.hpp"
#include "SceneStateMachine.hpp"
#include "Setup.hpp"
#include "GuiManager.hpp"
#include "GuiLayout.hpp"
#include "GuiLayoutVertical.hpp"
#include "GuiLayoutHorizontal.hpp"
#include "GuiObject.hpp"
#include "GuiTextWidget.hpp"

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
  Setup m_setup;

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
