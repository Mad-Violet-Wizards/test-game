#pragma once

#include <thread>
#include <future>

#include "Window.hpp"
#include "SceneStateMachine.hpp"

#include "GuiManager.hpp"
#include "GuiLayoutVertical.hpp"
#include "GuiTextWidget.hpp"

class Game;

class SceneLoading : public Scene
{

  public:

    SceneLoading(Window *window);
    ~SceneLoading();

    void OnCreate() override;
    void OnDestroy() override;

    void Update(float deltaTime) override;
    void LateUpdate(float deltaTime) override;
    void Draw(Window &window) override;

  private:

    void CreateGUI();

  private:

    Window *m_window;

    GuiManager m_guiManager;
    std::shared_ptr<GuiLayoutVertical> m_loadingLayout;
    std::shared_ptr<GuiTextWidget> m_loadingText;
};
