#pragma once

#include <string>
#include <map>
#include <vector>
#include "Animation.hpp"

struct ProjectileData
{
  std::string NAME;

  std::string TEXTURE_NAME;

  std::unordered_map<FacingDirection, sf::IntRect> TEXTURE;
  std::unordered_map<FacingDirection, sf::Vector2f> OFFSET;
  std::unordered_map<FacingDirection, sf::Vector2f> VELOCITY;
};

class ProjectileStorage
{
  
  public:

    ProjectileStorage();
    ~ProjectileStorage();

    static void Initialize();

    static const ProjectileData &GetProjectileData(const std::string &name);

  private:

    static std::vector<ProjectileData> m_projectileData;

};