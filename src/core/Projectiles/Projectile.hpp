#pragma once

#include <string>
#include <map>

#include "Animation.hpp"

class Projectile
{

  public:

    Projectile(const std::string &name);
    virtual ~Projectile() = default;

    const std::unordered_map<FacingDirection, sf::IntRect> &GetTexture() const;
    const std::unordered_map<FacingDirection, sf::Vector2f> &GetOffset() const;
    const std::unordered_map<FacingDirection, sf::Vector2f> &GetVelocity() const;

  public:

      std::string m_name;
      std::string m_textureName;

  protected:
  
      std::unordered_map<FacingDirection, sf::IntRect> m_texture;
      std::unordered_map<FacingDirection, sf::Vector2f> m_offset;
      std::unordered_map<FacingDirection, sf::Vector2f> m_velocity;
};