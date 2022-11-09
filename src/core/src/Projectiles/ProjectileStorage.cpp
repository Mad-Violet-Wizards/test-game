#include "ProjectileStorage.hpp"

std::vector<ProjectileData> ProjectileStorage::m_projectileData = std::vector<ProjectileData>();

ProjectileStorage::ProjectileStorage()
{
  ProjectileData ARROW;

  ARROW.NAME = "Arrow";

  ARROW.TEXTURE_NAME = "projectile_arrow.dat";

  ARROW.TEXTURE.emplace(FacingDirection::North, sf::IntRect(0, 0, 32, 32));
  ARROW.TEXTURE.emplace(FacingDirection::East,  sf::IntRect(32, 0, 32, 32));
  ARROW.TEXTURE.emplace(FacingDirection::South,  sf::IntRect(64, 0, 32, 32));
  ARROW.TEXTURE.emplace(FacingDirection::West,  sf::IntRect(96, 0, 32, 32));

  ARROW.OFFSET.emplace(FacingDirection::North, sf::Vector2f(0.f, 0.f));
  ARROW.OFFSET.emplace(FacingDirection::East, sf::Vector2f(0.f, 0.f));
  ARROW.OFFSET.emplace(FacingDirection::South, sf::Vector2f(0.f, 0.f));
  ARROW.OFFSET.emplace(FacingDirection::West, sf::Vector2f(0.f, 0.f));

  ARROW.VELOCITY.emplace(FacingDirection::North, sf::Vector2f(0.f, -1.f));
  ARROW.VELOCITY.emplace(FacingDirection::East, sf::Vector2f(1.f, 0.f));
  ARROW.VELOCITY.emplace(FacingDirection::South, sf::Vector2f(0.f, 1.f));
  ARROW.VELOCITY.emplace(FacingDirection::West, sf::Vector2f(-1.f, 0.f));

  m_projectileData.push_back(ARROW);
}

ProjectileStorage::~ProjectileStorage()
{

}

const ProjectileData &ProjectileStorage::GetProjectileData(const std::string &name)
{
  for (auto &projectileData : m_projectileData)
  {
    if (projectileData.NAME == name)
    {
      return projectileData;
    }
  }

  return m_projectileData[0];
}