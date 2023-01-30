#include "C_Velocity.hpp"
#include "C_Transform.hpp"

C_Velocity::C_Velocity(Object *owner) 
  : Component(owner), 
  m_maxVelocity(300.f, 300.f) {}

void C_Velocity::Update(float deltaTime)
{
  sf::Vector2f absoluteVelocity(m_velocity * deltaTime);
  owner -> transform -> AddPosition(absoluteVelocity);
}

void C_Velocity::Set(const sf::Vector2f &velocity)
{
  m_velocity = velocity;
  ClampVelocity();
}

void C_Velocity::Set(float x, float y)
{
  m_velocity.x = x;
  m_velocity.y = y;

  ClampVelocity();
}

const sf::Vector2f &C_Velocity::Get() const
{
  return m_velocity;
}

void C_Velocity::ClampVelocity()
{
  if (fabs(m_velocity.x) > m_maxVelocity.x)
  {
    if (m_velocity.x > 0.f) 
    { 
      m_velocity.x = m_maxVelocity.x; 
    }
    else 
    { 
      m_velocity.x = -m_maxVelocity.x; 
    }
  }

  if (fabs(m_velocity.y) > m_maxVelocity.y)
  {
    if (m_velocity.y > 0.f) 
    {
      m_velocity.y = m_maxVelocity.y;
    }
    else
    {
      m_velocity.y = -m_maxVelocity.y;
    }
  }
}