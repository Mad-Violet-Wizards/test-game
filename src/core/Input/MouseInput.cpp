#include "MouseInput.hpp"

#include "Bitmask.hpp"

MouseInput::MouseInput()
{
  InitializeAssociatedKeys();
}

MouseInput::~MouseInput()
{
}

void MouseInput::InitializeAssociatedKeys()
{
  m_associatedKeys.insert({ sf::Mouse::Left, MouseKey::Left });
  m_associatedKeys.insert({ sf::Mouse::Right, MouseKey::Right });
  m_associatedKeys.insert({ sf::Mouse::Middle, MouseKey::Middle });
}

void MouseInput::UpdateKeyPressed(int mouseKeyCode)
{
  m_lastFrameKeys = m_currentFrameKeys;

  auto associatedPair = m_associatedKeys.find(static_cast<sf::Mouse::Button>(mouseKeyCode));

  if (associatedPair != m_associatedKeys.end())
  {
    m_currentFrameKeys.SetBit(static_cast<int>(associatedPair -> second), 1);
  }
}

void MouseInput::UpdateKeyReleased(int mouseKeyCode)
{
  m_lastFrameKeys = m_currentFrameKeys;

  auto associatedPair = m_associatedKeys.find(static_cast<sf::Mouse::Button>(mouseKeyCode));

  if (associatedPair != m_associatedKeys.end())
  {
    m_currentFrameKeys.SetBit(static_cast<int>(associatedPair -> second), 0);
  }
}

bool MouseInput::IsMouseKeyPressed(MouseKey mouseKeyCode)
{
  return m_currentFrameKeys.GetBit(static_cast<int>(mouseKeyCode));
}

bool MouseInput::IsMouseKeyReleased(MouseKey mouseKeyCode)
{
  bool lastFrame    = m_lastFrameKeys.GetBit(static_cast<int>(mouseKeyCode));
  bool currentFrame = m_currentFrameKeys.GetBit(static_cast<int>(mouseKeyCode));

  //
  // Reset of the bits is required because the Mouse Event
  // is something that actually should be reported only once
  // so we're preventing from having the issue with immadietly
  // clicking the two buttons when they're on the same position
  // and first one is supposed to show the second one.
  //

  m_lastFrameKeys.SetBit(static_cast<int>(mouseKeyCode), 0);
  m_currentFrameKeys.SetBit(static_cast<int>(mouseKeyCode), 0);

  return currentFrame && !lastFrame;
}