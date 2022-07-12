#pragma once

#include "Component.hpp"
#include "C_Velocity.hpp"

class C_KeyboardMovement : public Component
{

public:

  C_KeyboardMovement(Object *owner);

  void Awake() override;
  void SetMovementSpeed(int moveSpeed);
  void Update(float deltaTime) override;

private:

  float m_moveSpeed;

  std::shared_ptr<C_Velocity> m_velocity;

};
