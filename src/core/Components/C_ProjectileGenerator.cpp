#include "C_ProjectileGenerator.hpp"

#include "ProjectileStorage.hpp"
#include "Projectile.hpp"

#include "C_Sprite.hpp"
#include "C_Drawable.hpp"
#include "C_Velocity.hpp"
#include "C_ColliderBox.hpp"
#include "C_RemoveObjectOnCollisionEnter.hpp"
#include "C_Direction.hpp"

C_ProjectileGenerator::C_ProjectileGenerator(Object *owner, ObjectCollection *objectCollection)
  : Component(owner),
  m_objectCollection(objectCollection)
{
}

void C_ProjectileGenerator::Awake()
{
  m_direction = owner -> GetComponent<C_Direction>();
}

void C_ProjectileGenerator::GenerateProjectile(const std::string &name)
{
  FacingDirection direction = m_direction -> GetDirection();

  Projectile projectileData = ProjectileStorage::GetProjectileData(name);

  std::shared_ptr<Object> projectile = std::make_shared<Object>();

  projectile -> transform -> SetPosition(owner -> transform -> GetPosition() + projectileData.GetOffset().at(direction));

  auto projectileSprite = projectile -> AddComponent<C_Sprite>();
  projectileSprite -> Load(AssetsStorage::GetInstance().GetTexture(projectileData.m_textureName));
  projectileSprite -> SetTextureRect(projectileData.GetTexture().at(direction));

  auto projectileVelocity = projectile -> AddComponent<C_Velocity>();
  projectileVelocity -> Set(projectileData.GetVelocity().at(direction) * 500.f);

  auto projectileDrawable = projectile -> AddComponent<C_Drawable>();
  projectileDrawable -> SetLayer(0);

  auto projectileCollider = projectile -> AddComponent<C_ColliderBox>();
  projectileCollider -> SetLayer(0);
  projectileCollider -> SetSize(32.f, 32.f);

  projectile -> AddComponent<C_RemoveObjectOnCollisionEnter>();

  m_objectCollection -> Add(projectile);
}