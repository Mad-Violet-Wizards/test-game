#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "Window.hpp"
#include "GuiManager.hpp"
#include "GuiLayout.hpp"
#include "GuiLayoutVertical.hpp"
#include "GuiLayoutHorizontal.hpp"
#include "GuiObject.hpp"
#include "GuiTextWidget.hpp"

class SceneMenu : public Scene
{
public:

  SceneMenu(Window *window);
  ~SceneMenu();

  void OnCreate() override;
  void OnDestroy() override;

  void ProcessInput() override;
  void Update(float deltaTime) override;
  void Draw(Window &window) override;

  void Test();

private:

  void InitConnections();

private:

  GuiManager m_menuGuiManager;

  std::shared_ptr<GuiLayout> m_menuLayout;
  std::shared_ptr<GuiLayoutVertical> m_testVerticalLayout;
  std::shared_ptr<GuiTextWidget> m_buttonNewGame;
  std::shared_ptr<GuiTextWidget> m_buttonLoadGame;
  std::shared_ptr<GuiTextWidget> m_buttonOptions;
  std::shared_ptr<GuiTextWidget> m_buttonExit;

  Input m_input;

  Window *m_window;
};
