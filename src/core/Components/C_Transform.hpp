#pragma once

#include "Component.hpp"

class C_Transform : public Component
{

public:

  C_Transform(Object *owner);

  void LateUpdate(float deltaTime) override;

  void SetPosition(float x, float y);
  void SetPosition(const sf::Vector2f &pos);

  void AddPosition(float x, float y);
  void AddPosition(const sf::Vector2f &pos);

  void SetX(float x);
  void SetY(float y);

  void AddX(float x);
  void AddY(float y);

  const sf::Vector2f &GetPosition() const;
  const sf::Vector2f &GetPreviousFramePosition() const;

  void SetStatic(bool isStatic);
  bool IsStatic() const;

private:

  sf::Vector2f m_position;
  sf::Vector2f m_previousFramePosition;
  bool m_isStaticTransform;

};
