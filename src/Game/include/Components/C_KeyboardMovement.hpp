#pragma once

#include "Component.hpp"

class C_KeyboardMovement : public Component
{

public:

  C_KeyboardMovement(Object *owner);

  void SetMovementSpeed(int moveSpeed);
  void Update(float deltaTime) override;

private:

  int m_moveSpeed;

};
