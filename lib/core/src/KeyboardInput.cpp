#include <iostream>

#include "KeyboardInput.hpp"

KeyboardInput::KeyboardInput()
{
  std::cout << "[KeyboardInput] Created new instance of Keyboard input.\n";
  InitializeAssociatedKeys();
}

KeyboardInput::~KeyboardInput()
{
  std::cout << "[KeyboardInput] Deleted instance of Keyboard input.\n";
}

void KeyboardInput::InitializeAssociatedKeys()
{
  m_associatedKeys.insert({ sf::Keyboard::W, Key::Up});
  m_associatedKeys.insert({ sf::Keyboard::A, Key::Left });
  m_associatedKeys.insert({ sf::Keyboard::S, Key::Down });
  m_associatedKeys.insert({ sf::Keyboard::D, Key::Right });
}

void KeyboardInput::UpdateKeyPressed(int keyCode)
{
  m_lastFrameKeys.SetMask(m_currentFrameKeys);

  auto associatedPair = m_associatedKeys.find(static_cast<sf::Keyboard::Key>(keyCode));

  if (associatedPair != m_associatedKeys.end())
  {
    m_currentFrameKeys.SetBit(static_cast<int>(associatedPair -> second), 1);
  }
}

void KeyboardInput::UpdateKeyReleased(int keyCode)
{
  m_lastFrameKeys.SetMask(m_currentFrameKeys);

  auto associatedPair = m_associatedKeys.find(static_cast<sf::Keyboard::Key>(keyCode));

  if (associatedPair != m_associatedKeys.end())
  {
    m_currentFrameKeys.SetBit(static_cast<int>(associatedPair -> second), 0);
  }
}

bool KeyboardInput::IsKeyPressed(Key keyCode)
{
  return m_currentFrameKeys.GetBit(static_cast<int>(keyCode));
}

bool KeyboardInput::IsKeyDown(Key keyCode)
{
  bool lastFrame    = m_lastFrameKeys.GetBit(static_cast<int>(keyCode));
  bool currentFrame = m_currentFrameKeys.GetBit(static_cast<int>(keyCode));

  return currentFrame && !lastFrame;
}

bool KeyboardInput::IsKeyUp(Key keyCode)
{
  bool lastFrame    = m_lastFrameKeys.GetBit(static_cast<int>(keyCode));
  bool currentFrame = m_currentFrameKeys.GetBit(static_cast<int>(keyCode));

  return !currentFrame && lastFrame;
}