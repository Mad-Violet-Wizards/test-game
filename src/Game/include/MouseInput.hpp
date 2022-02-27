#pragma once

#include <memory>

/*
  This class contains operations provided by Mouse.
  It will get extended when we'll need new operations 
  (such like WheelEvent, or Pressed Mouse Button).
*/

class MouseInput
{
  public:

    typedef enum
    {
      Left,
      Right
    } MouseButton;

    typedef struct
    {
      bool MouseLeftReleased;
      bool MouseRightReleased;
    } MouseEvent;

    ~MouseInput();
    static MouseInput &GetInstance();

    void SetMouseReleasedEvent(MouseInput::MouseButton button, bool released);
    bool MouseReleasedEvent(MouseInput::MouseButton button) const;

    void ResetEvents();

  private:

    MouseInput();

  private:
    static std::unique_ptr<MouseInput> s_instance;

    MouseEvent m_mouseEvent;
};