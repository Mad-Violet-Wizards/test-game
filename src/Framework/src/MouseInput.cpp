#include <iostream>

#include "MouseInput.hpp"

MouseInput::MouseInput()
{
  std::cout << "[MouseInput] Created new instance of Mouse input.\n";
  InitializeAssociatedKeys();
}

MouseInput::~MouseInput()
{
  std::cout << "[MouseInput] Deleted instance of Mouse input.\n";
}

void MouseInput::InitializeAssociatedKeys()
{
  m_associatedKeys.insert({ sf::Mouse::Left, MouseKey::Left });
  m_associatedKeys.insert({ sf::Mouse::Right, MouseKey::Right });
  m_associatedKeys.insert({ sf::Mouse::Middle, MouseKey::Middle });
}

void MouseInput::UpdateKeyPressed(int mouseKeyCode)
{
  m_lastFrameKeys.SetMask(m_currentFrameKeys);

  auto associatedPair = m_associatedKeys.find((sf::Mouse::Button) mouseKeyCode);

  if (associatedPair != m_associatedKeys.end())
  {
    m_currentFrameKeys.SetBit((int) associatedPair -> second, 1);
  }
}

void MouseInput::UpdateKeyReleased(int mouseKeyCode)
{
  m_lastFrameKeys.SetMask(m_currentFrameKeys);

  auto associatedPair = m_associatedKeys.find((sf::Mouse::Button) mouseKeyCode);

  if (associatedPair != m_associatedKeys.end())
  {
    m_currentFrameKeys.SetBit((int) associatedPair -> second, 0);
  }
}

bool MouseInput::IsMouseKeyPressed(MouseKey key)
{
  return m_currentFrameKeys.GetBit((int)key);
}

bool MouseInput::IsMouseKeyReleased(MouseKey key)
{
  bool lastFrame = m_lastFrameKeys.GetBit((int)key);
  bool currentFrame = m_currentFrameKeys.GetBit((int)key);

  //
  // Reset of the bits is required because the Mouse Event
  // is something that actually should be reported only once
  // so we're preventing from having the issue with immadietly
  // clicking the two buttons when they're on the same position
  // and first one is supposed to show the second one.
  //

  m_lastFrameKeys.SetBit((int) key, 0);
  m_currentFrameKeys.SetBit((int) key, 0);

  return currentFrame && !lastFrame;
}