#pragma once

#include "Input/KeyboardInput.hpp"
#include "Input/MouseInput.hpp"

#include "Design-Patterns/Singleton.hpp"

class EventHandler
{

public:

  EventHandler() = default;
  ~EventHandler() = default;

  KeyboardInput &GetKeyboardInput();
  MouseInput &GetMouseInput();

  void ProcessEvent(const sf::Event &event);

private:

  KeyboardInput m_keyboardInput;
  MouseInput m_mouseInput;

};

using EventHandlerSingleton = Singleton<EventHandler>;