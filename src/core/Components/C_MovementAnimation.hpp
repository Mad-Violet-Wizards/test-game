#pragma once

#include "Component.hpp"

class C_Velocity;
class C_Animation;

class C_MovementAnimation : public Component
{

public:

  C_MovementAnimation(Object *owner);

  void Awake() override;

  void Update(float deltaTime) override;

private:

  std::shared_ptr<C_Velocity> m_velocity;
  std::shared_ptr<C_Animation> m_animation;

};