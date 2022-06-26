#pragma once

#include <SFML/Graphics.hpp>

#include "KeyboardInput.hpp"
#include "MouseInput.hpp"

class EventHandler
{

public:

  ~EventHandler();

  static EventHandler &GetInstance();
  KeyboardInput &GetKeyboardInput();
  MouseInput &GetMouseInput();

  void ProcessEvent(const sf::Event &event);

private:

  EventHandler();

private:

  KeyboardInput m_keyboardInput;
  MouseInput m_mouseInput;

  static std::unique_ptr<EventHandler> s_instance;

};