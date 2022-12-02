#pragma once

#include "Projectile.hpp"

class ProjectileArrow : public Projectile
{

  public:

    ProjectileArrow(const std::string &name);
    ~ProjectileArrow() = default;

};