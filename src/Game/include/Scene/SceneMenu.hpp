#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "Window.hpp"
#include "GuiManager.hpp"
#include "GuiLayout.hpp"
#include "GuiWidget.hpp"
#include "GuiTextWidget.hpp"
#include "Widgets/Button_NewGame.hpp"
#include "Widgets/Button_LoadGame.hpp"
#include "Widgets/Button_Options.hpp"
#include "Widgets/Button_Exit.hpp"

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
  std::shared_ptr<Button_NewGame> m_ButtonNewGame;
  std::shared_ptr<Button_LoadGame> m_ButtonLoadGame;
  std::shared_ptr<Button_Options> m_ButtonOptions;
  std::shared_ptr<Button_Exit> m_ButtonExit;
  std::shared_ptr<GuiTextWidget> m_test;


  Window* m_window;
};
