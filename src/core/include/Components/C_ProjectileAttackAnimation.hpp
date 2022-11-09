#pragma once

#include "Component.hpp"
#include "C_Animation.hpp"
#include "C_Direction.hpp"
#include "C_ProjectileGenerator.hpp"

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