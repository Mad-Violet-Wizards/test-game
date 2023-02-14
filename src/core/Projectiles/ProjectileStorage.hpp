#pragma once

#include "Projectile.hpp"

class ProjectileStorage
{
  
  public:

    ProjectileStorage();
    ~ProjectileStorage();

    static void Initialize();

    static const Projectile &GetProjectileData(const std::string &name);

  private:

    static std::vector<Projectile> m_projectileData;

};