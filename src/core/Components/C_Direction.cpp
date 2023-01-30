#include "C_Direction.hpp"

#include "Object.hpp"
#include "ConsoleLog.hpp"

C_Direction::C_Direction(Object *owner) 
  : Component(owner) {}

void C_Direction::Awake()
{
  m_velocity = owner -> GetComponent<C_Velocity>();
}

FacingDirection C_Direction::GetDirection()
{
  const sf::Vector2f &currentVelocity = m_velocity -> Get();

  if (currentVelocity.x != 0.f || currentVelocity.y != 0.f)
  {
    float absVelocityX = fabs(currentVelocity.x);
    float absVelocityY = fabs(currentVelocity.y);

    if (absVelocityX > absVelocityY)
    {
      if (currentVelocity.x < 0)
      {
        m_currentDirection = FacingDirection::West;
      }
      else
      {
        m_currentDirection = FacingDirection::East;
      }
    } 
    else
    {
      if (currentVelocity.y < 0)
      {
        m_currentDirection = FacingDirection::North;
      }
      else
      {
        m_currentDirection = FacingDirection::South;
      }
    }
  }

  return m_currentDirection;
}

sf::Vector2i C_Direction::GetHeading()
{
  FacingDirection direction = GetDirection();

  sf::Vector2i heading;

  if (direction == FacingDirection::North)
  {
    heading.y = -1;
  }
  else if (direction == FacingDirection::East)
  {
    heading.x = 1;
  }
  else if (direction == FacingDirection::South)
  {
    heading.y = 1;
  }
  else if (direction == FacingDirection::West)
  {
    heading.x = -1;
  }

  return heading;
}