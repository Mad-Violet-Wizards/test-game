#include <iostream>

#include "KeyboardInput.hpp"

KeyboardInput::KeyboardInput()
{
  InitializeAssociatedKeys();
}

KeyboardInput::~KeyboardInput()
{
}

void KeyboardInput::InitializeAssociatedKeys()
{
  m_associatedKeys.insert({ sf::Keyboard::W, Key::Up});
  m_associatedKeys.insert({ sf::Keyboard::A, Key::Left });
  m_associatedKeys.insert({ sf::Keyboard::S, Key::Down });
  m_associatedKeys.insert({ sf::Keyboard::D, Key::Right });
  m_associatedKeys.insert({ sf::Keyboard::E, Key::E });
}

void KeyboardInput::UpdateKeyPressed(int keyCode)
{
  m_lastFrameKeys = m_currentFrameKeys;

  auto associatedPair = m_associatedKeys.find(static_cast<sf::Keyboard::Key>(keyCode));

  if (associatedPair != m_associatedKeys.end())
  {
    m_currentFrameKeys.SetBit(static_cast<int>(associatedPair -> second), 1);
  }
}

void KeyboardInput::UpdateKeyReleased(int keyCode)
{
  m_lastFrameKeys = m_currentFrameKeys;

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