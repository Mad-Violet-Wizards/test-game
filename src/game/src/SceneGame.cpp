#include <iostream>

#include "SceneGame.hpp"
#include "AssetsManager.hpp"
#include "Directory.hpp"
#include "tileson.hpp"

#ifdef DEBUG
#include "Debug.hpp"
#endif

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate()
{
  m_player = std::make_shared<Object>();
  m_player -> SetDrawable(true);
  m_player -> SetCollidable(true);

  auto sprite = m_player -> AddComponent<C_Sprite>();

  auto transform = m_player -> AddComponent<C_Transform>();

  auto velocity = m_player -> AddComponent<C_Velocity>();

  auto movement = m_player -> AddComponent<C_KeyboardMovement>();
  movement -> Awake();

  auto animation = m_player -> AddComponent<C_Animation>();
  animation -> Awake();
  animation -> SetAnimationFile(Directory::ANIMATIONS_DIRECTORY + "AnimationPlayerTest.json");

  auto movementAnimation = m_player -> AddComponent<C_MovementAnimation>();
  movementAnimation -> Awake();

  auto collider = m_player -> AddComponent<C_ColliderBox>();
  collider -> SetSize(32.f, 32.f);

  m_objects.Add(m_mapParser.ParseMap(Directory::MAPS_DIRECTORY + "TestMap.json"));
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

  #ifdef DEBUG
  Debug::Draw(window);
  #endif
}