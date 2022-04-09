#include <iostream>

#include "MouseInput.hpp"

std::unique_ptr<MouseInput> MouseInput::s_instance = nullptr;

MouseInput::MouseInput()
{
  m_mouseEvent.MouseLeftReleased = false;
  m_mouseEvent.MouseRightReleased = false;
}

MouseInput::~MouseInput()
{

}

MouseInput &MouseInput::GetInstance()
{

  if (MouseInput::s_instance == nullptr)
  {
    MouseInput::s_instance = std::unique_ptr<MouseInput>(new MouseInput);
  }

  return *s_instance;
}

void MouseInput::SetMouseReleasedEvent(MouseInput::MouseButton button, bool released)
{
  switch (button)
  {
    case MouseInput::MouseButton::Left:
    {
      m_mouseEvent.MouseLeftReleased = released;
      break;
    }
    case MouseInput::MouseButton::Right:
    {
      m_mouseEvent.MouseRightReleased = released;
      break;
    }
  }
}

bool MouseInput::MouseReleasedEvent(MouseInput::MouseButton button) const
{
  switch (button)
  {
    case MouseInput::MouseButton::Left:
    {
      return m_mouseEvent.MouseLeftReleased;
    }
    case MouseInput::MouseButton::Right:
    {
      return m_mouseEvent.MouseRightReleased;
    }
    default:
    {
      return false;
    }
  }
}

void MouseInput::ResetEvents()
{
  m_mouseEvent.MouseLeftReleased = false;
  m_mouseEvent.MouseRightReleased = false;
}