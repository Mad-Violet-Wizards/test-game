#include <iostream>
#include <SFML/Graphics.hpp>

#include "Scene/SceneMenu.hpp"


SceneMenu::SceneMenu() 
{
	sf::RectangleShape testWidget;
	testWidget.setSize(sf::Vector2f(200, 200));
	testWidget.setFillColor(sf::Color(255, 0, 0));

	sf::RectangleShape testWidget2;
	testWidget2.setSize(sf::Vector2f(200, 200));
	testWidget2.setFillColor(sf::Color(0, 255, 255));
	testWidget2.setPosition(300, 300);

	m_menuLayout.AddWidget(testWidget);
	m_testLayout.AddWidget(testWidget2);

	m_menuGuiManager.AddLayout(m_menuLayout);
	m_menuGuiManager.AddLayout(m_testLayout);
}

SceneMenu::~SceneMenu() {}

void SceneMenu::OnCreate()
{
	
}

void SceneMenu::OnDestroy()
{

}

void SceneMenu::Update(float deltaTime)
{

}

void SceneMenu::Draw(Window& window)
{
	m_menuGuiManager.Draw(window);
}