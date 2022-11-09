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
    E = 6
  };

  KeyboardInput();
  ~KeyboardInput();

  void InitializeAssociatedKeys();

  void UpdateKeyPressed(int keyCode);
  void UpdateKeyReleased(int keyCode);

  bool IsKeyPressed(Key keyCode);
  bool IsKeyDown(Key keyCode);
  bool IsKeyUp(Key keyCode);

private:

  Bitmask m_currentFrameKeys;
  Bitmask m_lastFrameKeys;

  std::map<sf::Keyboard::Key, Key> m_associatedKeys;

};
