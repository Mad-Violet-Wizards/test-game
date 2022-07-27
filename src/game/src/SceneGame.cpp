#include <iostream>

#include "SceneGame.hpp"
#include "AssetsManager.hpp"

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate()
{
  m_player = std::make_shared<Object>();

  auto sprite = m_player -> AddComponent<C_Sprite>();

  auto transform = m_player -> AddComponent<C_Transform>();

  auto velocity = m_player -> AddComponent<C_Velocity>();

  auto movement = m_player -> AddComponent<C_KeyboardMovement>();
  movement -> Awake();

  auto animation = m_player -> AddComponent<C_Animation>();
  animation -> Awake();
  animation -> SetAnimationFile("../assets/animations/AnimationPlayer.json");

  auto movementAnimation = m_player -> AddComponent<C_MovementAnimation>();
  movementAnimation -> Awake();

  m_objects.Add(m_player);
}

void SceneGame::OnDestroy() {}

void SceneGame::Update(float deltaTime)
{
  m_objects.ProcessRemovedObjects();
  m_objects.ProcessNewObjects();

  m_objects.Update(deltaTime);
}

void SceneGame::Draw(Window& window)
{
  m_objects.Draw(window);
}