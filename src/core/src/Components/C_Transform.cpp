#include "C_Transform.hpp"

C_Transform::C_Transform(Object *owner) 
  : Component(owner),
    m_position(0.f, 0.f),
    m_previousFramePosition{0.f, 0.f},
    m_isStaticTransform(false)
{
}

void C_Transform::LateUpdate(float deltaTime)
{
  if (!m_isStaticTransform)
  {
    m_previousFramePosition = m_position;
  }
}

void C_Transform::SetPosition(float x, float y)
{
  m_position.x = x;
  m_position.y = y;
}

void C_Transform::SetPosition(sf::Vector2f &pos)
{
  m_position = pos;
}

void C_Transform::AddPosition(float x, float y)
{
  m_position.x += x;
  m_position.y += y;
}

void C_Transform::AddPosition(sf::Vector2f &pos)
{
  m_position += pos;
}

void C_Transform::SetX(float x)
{
  m_position.x = x;
}

void C_Transform::SetY(float y)
{
  m_position.y = y;
}

void C_Transform::AddX(float x)
{
  m_position.x += x;
}

void C_Transform::AddY(float y)
{
  m_position.y += y;
}

const sf::Vector2f &C_Transform::GetPosition() const
{
  return m_position;
}

const sf::Vector2f &C_Transform::GetPreviousFramePosition() const
{
  return m_previousFramePosition;
}

void C_Transform::SetStatic(bool isStatic)
{
  m_isStaticTransform = isStatic;
}

bool C_Transform::IsStatic() const
{
  return m_isStaticTransform;
}