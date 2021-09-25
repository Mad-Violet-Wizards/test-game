#pragma once

#include <memory>

#include "Scene/Scene.hpp"
#include "GuiManager.hpp"

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
		// GuiLayout m_menuLayout;
		std::shared_ptr<GuiLayout> m_testLayout;
};
