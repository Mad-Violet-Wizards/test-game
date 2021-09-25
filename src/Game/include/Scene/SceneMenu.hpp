#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "GuiManager.hpp"
#include "GuiLayout.hpp"
#include "GuiWidget.hpp"
#include "GuiTextWidget.hpp"

class SceneMenu : public Scene
{
	public:

		SceneMenu();
		~SceneMenu();

		void OnCreate() override;
		void OnDestroy() override;

		void Update(float deltaTime) override;
		void Draw(Window& window) override;

	private:

    GuiManager m_menuGuiManager;
    
    std::shared_ptr<GuiLayout> m_menuLayout;
		std::shared_ptr<GuiLayout> m_testLayout;

    std::shared_ptr<GuiWidget> m_test1;
    std::shared_ptr<GuiTextWidget> m_textWidget;
};
