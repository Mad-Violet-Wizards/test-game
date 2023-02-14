#pragma once

class MouseInput
{

public:

  enum class MouseKey
  {
    None = 0,
    Left = 1,
    Right = 2,
    Middle = 3
  };

  MouseInput();
  ~MouseInput();

  void InitializeAssociatedKeys();

  void UpdateKeyPressed(int mouseKeyCode);
  void UpdateKeyReleased(int mouseKeyCode);

  bool IsMouseKeyPressed(MouseKey mouseKeyCode);
  bool IsMouseKeyReleased(MouseKey mouseKeyCode);

private:

  Bitmask m_currentFrameKeys;
  Bitmask m_lastFrameKeys;

  std::map<sf::Mouse::Button, MouseKey> m_associatedKeys;

};
