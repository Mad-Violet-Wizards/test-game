#include "C_MovementAnimation.hpp"

C_MovementAnimation::C_MovementAnimation(Object* owner) 
  : Component(owner), 
  m_velocity(nullptr), 
  m_animation(nullptr) {}

void C_MovementAnimation::Awake()
{
  m_velocity = m_owner -> GetComponent<C_Velocity>();
  m_animation = m_owner -> GetComponent<C_Animation>();
}

void C_MovementAnimation::Update(float deltaTime)
{
  const sf::Vector2f& currentVelocity = m_velocity -> Get();

  if (currentVelocity.x != 0.f || currentVelocity.y != 0.f)
  {
    m_animation -> SetAnimationState(AnimationState::Walk);

    float absVelocityX = fabs(currentVelocity.x);
    float absVelocityY = fabs(currentVelocity.y);

    if (absVelocityX > absVelocityY)
    {
      if (currentVelocity.x < 0.f)
      {
        m_animation -> SetAnimationDirection(FacingDirection::West);
      }
      else
      {
        m_animation -> SetAnimationDirection(FacingDirection::East);
      }
    }
    else
    {
      if (currentVelocity.y < 0.f)
      {
        m_animation -> SetAnimationDirection(FacingDirection::North);
      }
      else
      {
        m_animation -> SetAnimationDirection(FacingDirection::South);
      }
    }
  }
  else
  {
    m_animation -> SetAnimationState(AnimationState::Idle);
  }
}