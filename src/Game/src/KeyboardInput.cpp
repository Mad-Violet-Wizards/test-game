#include "KeyboardInput.hpp"

void KeyboardInput::Update()
{
  m_lastFrameKeys.SetMask(m_currentFrameKeys);

  m_currentFrameKeys.SetBit(
    (int)Key::Left,
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) ||
    (sf::Keyboard::isKeyPressed(sf::Keyboard::A)));

  m_currentFrameKeys.SetBit(
    (int)Key::Right,
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) ||
    (sf::Keyboard::isKeyPressed(sf::Keyboard::D)));

  m_currentFrameKeys.SetBit(
    (int)Key::Up,
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) ||
    (sf::Keyboard::isKeyPressed(sf::Keyboard::W)));

  m_currentFrameKeys.SetBit(
    (int)Key::Down,
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) ||
    (sf::Keyboard::isKeyPressed(sf::Keyboard::S)));

  m_currentFrameKeys.SetBit(
    (int)Key::Esc,
    (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)));
}

bool KeyboardInput::IsKeyPressed(Key keycode)
{
  return m_currentFrameKeys.GetBit((int)keycode);
}

bool KeyboardInput::IsKeyDown(Key keycode)
{
  bool lastFrame = m_lastFrameKeys.GetBit((int)keycode);
  bool currentFrame = m_currentFrameKeys.GetBit((int)keycode);

  return currentFrame && !lastFrame;
}

bool KeyboardInput::IsKeyUp(Key keycode)
{
  bool lastFrame = m_lastFrameKeys.GetBit((int)keycode);
  bool currentFrame = m_currentFrameKeys.GetBit((int)keycode);

  return !currentFrame && lastFrame;
}