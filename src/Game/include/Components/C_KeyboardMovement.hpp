#pragma once

#include "Components/Component.hpp"
#include "Input.hpp"

class C_KeyboardMovement : public Component
{
public:

  C_KeyboardMovement(Object *owner);

  void SetInput(Input *input);
  void SetMovementSpeed(int moveSpeed);
  void Update(float deltaTime) override;

private:

  int m_moveSpeed;
  Input *m_input;
};
