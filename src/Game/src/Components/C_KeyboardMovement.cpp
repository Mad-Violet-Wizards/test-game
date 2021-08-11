#include "Components/C_KeyboardMovement.hpp"
#include "Components/C_Transform.hpp"
#include "Object.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object* owner) : Component(owner), m_moveSpeed(100) {}

void C_KeyboardMovement::SetInput(Input* input)
{
  m_input = input;
}

void C_KeyboardMovement::Update(float deltaTime)
{
  if(m_input == nullptr)
  {
    return;
  }

  int xMove = 0;
  if (m_input -> IsKeyPressed(Input::Key::Left))
  {
    xMove = -m_moveSpeed;
  }
  else if (m_input -> IsKeyPressed(Input::Key::Right))
  {
    xMove = m_moveSpeed;
  }

  int yMove = 0;
  if (m_input -> IsKeyPressed(Input::Key::Up))
  {
    yMove = -m_moveSpeed;
  }
  else if (m_input -> IsKeyPressed(Input::Key::Down))
  {
    yMove = m_moveSpeed;
  }

  float xMoveFrame = xMove * deltaTime;
  float yMoveFrame = yMove * deltaTime;
  m_owner -> GetComponent<C_Transform>() -> AddPosition(xMoveFrame, yMoveFrame);
}
