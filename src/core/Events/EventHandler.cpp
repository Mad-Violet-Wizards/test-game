#include "EventHandler.hpp"

KeyboardInput &EventHandler::GetKeyboardInput()
{
  return m_keyboardInput;
}

MouseInput &EventHandler::GetMouseInput()
{
  return m_mouseInput;
}

void EventHandler::ProcessEvent(const sf::Event &event)
{
  if (event.type == sf::Event::KeyPressed)
  {
    m_keyboardInput.UpdateKeyPressed(event.key.code);
  }
  
  if (event.type == sf::Event::KeyReleased)
  {
    m_keyboardInput.UpdateKeyReleased(event.key.code);
  }

  if (event.type == sf::Event::MouseButtonPressed)
  {
    m_mouseInput.UpdateKeyPressed(event.mouseButton.button);
  }

  if (event.type == sf::Event::MouseButtonReleased)
  {
    m_mouseInput.UpdateKeyReleased(event.mouseButton.button);
  }

  if (event.type == sf::Event::LostFocus)
  {
    CONSOLE_LOG_INFO("[EventHandler] Reporting that Window has lost focus.");

    /*
    TODO: Implement a game freeze, and show of the pause menu when it will be implemented.
    */

  }

  if (event.type == sf::Event::GainedFocus)
  {
    CONSOLE_LOG_INFO("[EventHandler] Reporting that Window has gained focus.");

    /*
    TODO: Unfreeze the game.
    */

  }

  /*
  TODO: Add support for joysticks.
  */

}