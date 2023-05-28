#include "C_KeyboardMovement.hpp"
#include "C_Velocity.hpp"
#include "C_Transform.hpp"

C_KeyboardMovement::C_KeyboardMovement(Object *owner)
  : Component(owner),
  m_moveSpeed(100.f) {}

void C_KeyboardMovement::Awake()
{
  m_velocity = owner -> GetComponent<C_Velocity>();
}

EventHandler& eventHandler = EventHandlerSingleton::Instance();

void C_KeyboardMovement::Update(float deltaTime)
{
  float xMove = 0.f;
  if (eventHandler.GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Left))
  {
    xMove = -m_moveSpeed;
  }
  else if (eventHandler.GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Right))
  {
    xMove = m_moveSpeed;
  }

  float yMove = 0.f;
  if (eventHandler.GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Up))
  {
    yMove = -m_moveSpeed;
  }
  else if (eventHandler.GetKeyboardInput().IsKeyPressed(KeyboardInput::Key::Down))
  {
    yMove = m_moveSpeed;
  }

  m_velocity -> Set(xMove, yMove);
}
