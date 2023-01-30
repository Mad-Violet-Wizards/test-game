#include "ProjectileArrow.hpp"

ProjectileArrow::ProjectileArrow(const std::string &name)
  : Projectile(name)
{
  m_textureName = "projectile_arrow.png";

  m_texture.emplace(FacingDirection::North, sf::IntRect(0, 0, 32, 32));
  m_texture.emplace(FacingDirection::East,  sf::IntRect(32, 0, 32, 32));
  m_texture.emplace(FacingDirection::South,  sf::IntRect(64, 0, 32, 32));
  m_texture.emplace(FacingDirection::West,  sf::IntRect(96, 0, 32, 32));

  m_offset.emplace(FacingDirection::North, sf::Vector2f(0.f, -32.f));
  m_offset.emplace(FacingDirection::East, sf::Vector2f(32.f, 0.f));
  m_offset.emplace(FacingDirection::South, sf::Vector2f(0.f, 32.f));
  m_offset.emplace(FacingDirection::West, sf::Vector2f(-32.f, 0.f));

  m_velocity.emplace(FacingDirection::North, sf::Vector2f(0.f, -1.f));
  m_velocity.emplace(FacingDirection::East, sf::Vector2f(1.f, 0.f));
  m_velocity.emplace(FacingDirection::South, sf::Vector2f(0.f, 1.f));
  m_velocity.emplace(FacingDirection::West, sf::Vector2f(-1.f, 0.f));
}