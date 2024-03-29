#include "C_ProjectileAttackAnimation.hpp"

#include "C_Animation.hpp"
#include "C_Direction.hpp"
#include "C_ProjectileGenerator.hpp"
#include "KeyboardInput.hpp"

C_ProjectileAttackAnimation::C_ProjectileAttackAnimation(Object *owner)
  : Component(owner)
{
}

void C_ProjectileAttackAnimation::Awake()
{
  m_animation = owner -> GetComponent<C_Animation>();
  m_direction = owner -> GetComponent<C_Direction>();
  m_projectileGenerator = owner -> GetComponent<C_ProjectileGenerator>();
}

void C_ProjectileAttackAnimation::Start()
{
  m_animation -> AddAnimationAction(AnimationState::Projectile, FacingDirection::North, 3, std::bind(&C_ProjectileGenerator::GenerateProjectile, m_projectileGenerator, "Arrow"));
  m_animation -> AddAnimationAction(AnimationState::Projectile, FacingDirection::East,  3, std::bind(&C_ProjectileGenerator::GenerateProjectile, m_projectileGenerator, "Arrow"));
  m_animation -> AddAnimationAction(AnimationState::Projectile, FacingDirection::South, 3, std::bind(&C_ProjectileGenerator::GenerateProjectile, m_projectileGenerator, "Arrow"));
  m_animation -> AddAnimationAction(AnimationState::Projectile, FacingDirection::West,  3, std::bind(&C_ProjectileGenerator::GenerateProjectile, m_projectileGenerator, "Arrow"));
}

void C_ProjectileAttackAnimation::Update(float deltaTime)
{
  EventHandler& eventHandler = EventHandlerSingleton::Instance();

  if (eventHandler.GetKeyboardInput().IsKeyDown(KeyboardInput::Key::E))
  {
    m_animation -> SetAnimationState(AnimationState::Projectile);
  }
  else if (eventHandler.GetKeyboardInput().IsKeyUp(KeyboardInput::Key::E))
  {
    m_animation -> SetAnimationState(AnimationState::Idle);
  }
}