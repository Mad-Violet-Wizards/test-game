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

  SceneMenu(Window* window);
  ~SceneMenu();

  void OnCreate() override;
  void OnDestroy() override;

  void Update(float deltaTime) override;
  void Draw(Window& window) override;

private:

  GuiManager m_menuGuiManager;

  std::shared_ptr<GuiLayout> m_menuLayout;
  std::shared_ptr<GuiLayoutVertical> m_testVerticalLayout;
  std::shared_ptr<GuiTextWidget> m_test;
  std::shared_ptr<GuiTextWidget> m_test1;
  std::shared_ptr<GuiTextWidget> m_test2;
  std::shared_ptr<GuiTextWidget> m_test3;

  std::shared_ptr<GuiLayoutHorizontal> m_testHorizontalLayout;
  std::shared_ptr<GuiTextWidget> m_testH;
  std::shared_ptr<GuiTextWidget> m_testH1;
  std::shared_ptr<GuiTextWidget> m_testH2;
  std::shared_ptr<GuiTextWidget> m_testH3;
  Window* m_window;
};
