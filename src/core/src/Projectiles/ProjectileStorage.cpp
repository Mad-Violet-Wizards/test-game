#include "ProjectileStorage.hpp"

#include "ProjectileArrow.hpp"

std::vector<Projectile> ProjectileStorage::m_projectileData = std::vector<Projectile>();

ProjectileStorage::ProjectileStorage()
{}

ProjectileStorage::~ProjectileStorage()
{

}

void ProjectileStorage::Initialize()
{
  ProjectileArrow arrow("Arrow");

  m_projectileData.push_back(arrow);
}

const Projectile &ProjectileStorage::GetProjectileData(const std::string &name)
{
  for (auto &projectile : m_projectileData)
  {
    if (projectile.m_name == name)
    {
      return projectile;
    }
  }

  return m_projectileData[0];
}