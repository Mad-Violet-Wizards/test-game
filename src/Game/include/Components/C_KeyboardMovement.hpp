#pragma once

#include "Component.hpp"
#include "KeyboardInput.hpp"

class C_KeyboardMovement : public Component
{

public:

  C_KeyboardMovement(Object *owner);

  void SetInput(KeyboardInput *KeyboardInput);
  void SetMovementSpeed(int moveSpeed);
  void Update(float deltaTime) override;

private:

  int m_moveSpeed;
  KeyboardInput *m_keyboardInput;

};
