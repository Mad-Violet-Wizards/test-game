#include "Scene/SceneGame.hpp"

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate() 
{
  m_player = std::make_shared<Object>();
  auto sprite = m_player -> AddComponent<C_Sprite>();
  sprite -> Load("../../src/Assets/testsprite.png");

}

void SceneGame::OnDestroy() {}

void SceneGame::ProcessInput()
{
  m_input.Update();
}

void SceneGame::Update(float deltaTime) 
{

}

void SceneGame::Draw(Window& window) 
{
  m_player -> Draw(window);
}