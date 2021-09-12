#pragma once

#include "Scene/Scene.hpp"
#include "MenuWidget.hpp"

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

		MenuWidget m_menuWidget;
};
