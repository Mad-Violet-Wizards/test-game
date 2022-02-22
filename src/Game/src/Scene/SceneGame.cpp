#include "Scene/SceneGame.hpp"

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate()
{
  m_player = std::make_shared<Object>();
  auto sprite = m_player -> AddComponent<C_Sprite>();
  sprite->Load("../../src/Assets/testsprite.png");

  auto transform = m_player -> AddComponent<C_Transform>();

  auto movement = m_player -> AddComponent<C_KeyboardMovement>();
  movement -> SetInput(&m_input);
}

void SceneGame::OnDestroy() {}

void SceneGame::ProcessInput()
{
  m_input.Update();
}

void SceneGame::Update(float deltaTime)
{
  m_player -> Update(deltaTime);
}

void SceneGame::Draw(Window& window)
{
  m_player -> Draw(window);
}