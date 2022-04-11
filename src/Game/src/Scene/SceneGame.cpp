#include <iostream>

#include "SceneGame.hpp"
#include "EventHandler.hpp"

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate()
{
  m_player = std::make_shared<Object>();
  auto sprite = m_player -> AddComponent<C_Sprite>();
  sprite -> Load("../Assets/testsprite.png");

  auto transform = m_player -> AddComponent<C_Transform>();

  auto movement = m_player -> AddComponent<C_KeyboardMovement>();
}

void SceneGame::OnDestroy() {}

void SceneGame::Update(float deltaTime)
{
  m_player -> Update(deltaTime);
}

void SceneGame::Draw(Window& window)
{
  m_player -> Draw(window);
}