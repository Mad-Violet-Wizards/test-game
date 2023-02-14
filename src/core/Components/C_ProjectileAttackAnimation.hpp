#pragma once

#include "Component.hpp"

class C_Animation;
class C_Direction;
class C_ProjectileGenerator;

class C_ProjectileAttackAnimation : public Component
{

  public:

    C_ProjectileAttackAnimation(Object *owner);

    void Awake() override;

    void Start() override;

    void Update(float deltaTime) override;

  private:

    std::shared_ptr<C_Animation> m_animation;
    std::shared_ptr<C_Direction> m_direction;
    std::shared_ptr<C_ProjectileGenerator> m_projectileGenerator;

};