#pragma once

#include <cmath>

#include "Component.hpp"
#include "Object.hpp"

class C_Velocity : public Component
{

public:

  C_Velocity(Object *owner);

  void Update(float deltaTime) override;

  void Set(float x, float y);
  void Set(const sf::Vector2f &velocity);

  const sf::Vector2f &Get() const;

private:

  void ClampVelocity();

  sf::Vector2f m_velocity;
  sf::Vector2f m_maxVelocity;

};