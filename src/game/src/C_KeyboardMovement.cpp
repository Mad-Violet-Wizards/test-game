#include <iostream>

#include "C_KeyboardMovement.hpp"
#include "C_Transform.hpp"
#include "Object.hpp"
#include "EventHandler.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object *owner)
  : Component(owner),
  m_moveSpeed(100) {}

void C_KeyboardMovement::Awake()
{
  m_velocity = m_owner -> GetComponent<C_Velocity>();
}

void C_KeyboardMovement::Update(float deltaTime)
{
  float xMove = 0.f;
  if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Left))
  {
    xMove = -m_moveSpeed;
  }
  else if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Right))
  {
    xMove = m_moveSpeed;
  }

  float yMove = 0.f;
  if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Up))
  {
    yMove = -m_moveSpeed;
  }
  else if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Down))
  {
    yMove = m_moveSpeed;
  }

  m_velocity -> Set(xMove, yMove);
}
