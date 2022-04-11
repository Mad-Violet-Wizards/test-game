#include <iostream>

#include "Components/C_KeyboardMovement.hpp"
#include "Components/C_Transform.hpp"
#include "Object.hpp"
#include "EventHandler.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object *owner) : Component(owner), m_moveSpeed(100) {}

void C_KeyboardMovement::Update(float deltaTime)
{
  int xMove = 0;
  if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Left))
  {
    xMove = -m_moveSpeed;
  }
  else if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Right))
  {
    xMove = m_moveSpeed;
  }

  int yMove = 0;
  if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Up))
  {
    yMove = -m_moveSpeed;
  }
  else if (EventHandler::GetInstance().GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Down))
  {
    yMove = m_moveSpeed;
  }

  float xMoveFrame = xMove * deltaTime;
  float yMoveFrame = yMove * deltaTime;
  m_owner -> GetComponent<C_Transform>() -> AddPosition(xMoveFrame, yMoveFrame);
}
