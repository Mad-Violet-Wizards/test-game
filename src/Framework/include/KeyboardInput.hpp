#pragma once

#include <SFML/Graphics.hpp>
#include <map>

#include "Bitmask.hpp"

class KeyboardInput
{

public:

  enum class Key
  {
    None = 0,
    Left = 1,
    Right = 2,
    Up = 3,
    Down = 4,
    Esc = 5,
  };

  KeyboardInput();
  ~KeyboardInput();

  void InitializeAssociatedKeys();

  void UpdateKeyPressed(int keyCode);
  void UpdateKeyReleased(int keyCode);

  bool IsKeyPressed(Key keycode);
  bool IsKeyDown(Key keycode);
  bool IsKeyUp(Key keycode);

private:

  Bitmask m_currentFrameKeys;
  Bitmask m_lastFrameKeys;

  std::map<sf::Keyboard::Key, Key> m_associatedKeys;

};
