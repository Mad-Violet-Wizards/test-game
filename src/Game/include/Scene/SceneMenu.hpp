#pragma once

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
		GuiLayout m_menuLayout;
		GuiLayout m_testLayout;
};
