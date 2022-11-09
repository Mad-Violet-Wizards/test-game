#include "C_MovementAnimation.hpp"

C_MovementAnimation::C_MovementAnimation(Object* owner) 
  : Component(owner), 
  m_velocity(nullptr), 
  m_animation(nullptr) {}

void C_MovementAnimation::Awake()
{
  m_velocity = owner -> GetComponent<C_Velocity>();
  m_animation = owner -> GetComponent<C_Animation>();
}

void C_MovementAnimation::Update(float deltaTime)
{
  if (m_animation -> GetAnimationState() != AnimationState::Projectile)
  {
    const sf::Vector2f& currentVelocity = m_velocity -> Get();

    if (currentVelocity.x != 0.f || currentVelocity.y != 0.f)
    {
      m_animation -> SetAnimationState(AnimationState::Walk);
    }
    else
    {
      m_animation -> SetAnimationState(AnimationState::Idle);
    }
  }
}