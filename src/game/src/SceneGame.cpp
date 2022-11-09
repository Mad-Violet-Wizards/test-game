#include <iostream>

#include "SceneGame.hpp"
#include "AssetsStorage.hpp"
#include "AssetsStructure.hpp"

#include "C_Sprite.hpp"
#include "C_KeyboardMovement.hpp"
#include "C_Animation.hpp"
#include "C_Velocity.hpp"
#include "C_MovementAnimation.hpp"
#include "C_ColliderBox.hpp"
#include "C_Drawable.hpp"
#include "C_Direction.hpp"
#include "C_ProjectileAttackAnimation.hpp"
#include "C_ProjectileGenerator.hpp"

#include "tileson.hpp"

#ifdef DEBUG
#include "Debug.hpp"
#endif

SceneGame::SceneGame() {}

SceneGame::~SceneGame() {}

void SceneGame::OnCreate()
{
  const FacingDirection directions[4] = { FacingDirection::North, FacingDirection::East, FacingDirection::South, FacingDirection::West };

  m_player = std::make_shared<Object>();

  auto sprite = m_player -> AddComponent<C_Sprite>();

  auto velocity = m_player -> AddComponent<C_Velocity>();

  auto movement = m_player -> AddComponent<C_KeyboardMovement>();
  movement -> Awake();

  auto direction = m_player -> AddComponent<C_Direction>();
  direction -> Awake();

  auto projectileGenerator = m_player -> AddComponent<C_ProjectileGenerator>(&m_objects);
  projectileGenerator -> Awake();

  auto animation = m_player -> AddComponent<C_Animation>();
  animation -> Awake();
  animation -> SetAnimationFile(AssetsStructure::ANIMATIONS_DIRECTORY + "AnimationPlayerTest.json");

  auto projectileAttackAnimation = m_player -> AddComponent<C_ProjectileAttackAnimation>();
  projectileAttackAnimation -> Awake();

  // ADD PROJECTILE ANIMATIONS.
  const int projectileAnimationFrames = 4;
  const double delayBetweenFrames = 0.2;
  int initial_frame_pos_y = 256;

  std::map<FacingDirection, std::shared_ptr<Animation>> projectileAnimations;

  for (int i = 0; i < 4; i++)
  {
    std::shared_ptr<Animation> projectileAnimation = std::make_shared<Animation>();

    projectileAnimation -> SetLooped(true);

    for (int i = 0; i < projectileAnimationFrames; i++)
    {
      projectileAnimation->AddFrame(i * 32, initial_frame_pos_y, 32, 32, delayBetweenFrames);
    }

    projectileAnimations.insert({ directions[i], projectileAnimation });

    initial_frame_pos_y += 32;
  }

  animation -> AddAnimation(AnimationState::Projectile, projectileAnimations);

  auto movementAnimation = m_player -> AddComponent<C_MovementAnimation>();
  movementAnimation -> Awake();

  auto drawable = m_player -> AddComponent<C_Drawable>();
  drawable -> SetLayer(0);

  auto collider = m_player -> AddComponent<C_ColliderBox>();
  collider -> SetLayer(0);
  collider -> SetSize(32.f, 32.f);

  m_objects.Add(m_mapParser.ParseMap(AssetsStructure::MAPS_DIRECTORY + "TestMap.json"));
  m_objects.Add(m_player);
}

void SceneGame::OnDestroy() {}

void SceneGame::Update(float deltaTime)
{
  m_objects.ProcessRemovedObjects();
  m_objects.ProcessNewObjects();

  m_objects.Update(deltaTime);
}

void SceneGame::LateUpdate(float deltaTime)
{
  m_objects.LateUpdate(deltaTime);
}

void SceneGame::Draw(Window& window)
{
  m_objects.Draw(window);

  #ifdef DEBUG
  Debug::Draw(window);
  #endif
}