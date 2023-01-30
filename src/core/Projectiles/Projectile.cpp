#include "Projectile.hpp"

Projectile::Projectile(const std::string &name)
  : m_name(name)
{
}

const std::unordered_map<FacingDirection, sf::IntRect> &Projectile::GetTexture() const
{
  return m_texture;
}

const std::unordered_map<FacingDirection, sf::Vector2f> &Projectile::GetOffset() const
{
  return m_offset;
}

const std::unordered_map<FacingDirection, sf::Vector2f> &Projectile::GetVelocity() const
{
  return m_velocity;
}