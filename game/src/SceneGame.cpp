#include <iostream>

#include "SceneGame.hpp"

#include "AssetsManager.hpp"

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate()
{
  m_player = std::make_shared<Object>();
  auto sprite = m_player -> AddComponent<C_Sprite>();

  try
  {
    sprite -> Load(AssetsManager::GetInstance().GetTexture("testsprite"));
  }
  catch (const std::logic_error &exception)
  {
    std::cout << exception.what() << "\n";
  }
  catch (const std::runtime_error &exception)
  {
    std::cout << exception.what() << "\n";
  }

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