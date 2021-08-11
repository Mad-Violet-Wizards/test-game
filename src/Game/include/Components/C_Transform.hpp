#pragma once

#include "Components/Component.hpp"

class C_Transform : public Component
{
  public:

    C_Transform(Object* owner);

    void SetPosition(float x, float y);
    void SetPosition(sf::Vector2f& pos);

    void AddPosition(float x, float y);
    void AddPosition(sf::Vector2f& pos);

    void SetX(float x);
    void SetY(float y);

    void AddX(float x);
    void AddY(float y);

    const sf::Vector2f& GetPosition() const;

  private:

    sf::Vector2f m_position;
};
