#pragma once

#include "Component.hpp"

class C_Velocity;

class C_Direction : public Component
{

  public:

    C_Direction(Object *owner);

    void Awake() override;

    FacingDirection GetDirection();

    sf::Vector2i GetHeading();

  private:

    std::shared_ptr<C_Velocity> m_velocity;
    
    FacingDirection m_currentDirection;
};