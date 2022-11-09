#include "C_ProjectileGenerator.hpp"

#include "ProjectileStorage.hpp"
#include "ConsoleLog.hpp"

#include "C_Sprite.hpp"
#include "C_Drawable.hpp"
#include "C_Velocity.hpp"

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

  ProjectileData projectileData = ProjectileStorage::GetProjectileData(name);

  std::shared_ptr<Object> projectile = std::make_shared<Object>();

  projectile -> transform -> SetPosition(owner -> transform -> GetPosition() + projectileData.OFFSET.at(direction));

  auto projectileSprite = projectile -> AddComponent<C_Sprite>();
  projectileSprite -> Load(AssetsStorage::GetInstance().GetTexture(projectileData.TEXTURE_NAME));
  projectileSprite -> SetTextureRect(projectileData.TEXTURE.at(direction));

  auto projectileVelocity = projectile -> AddComponent<C_Velocity>();
  projectileVelocity -> Set(projectileData.VELOCITY.at(direction) * 500.f);

  auto projectileDrawable = projectile -> AddComponent<C_Drawable>();
  projectileDrawable -> SetLayer(0);

  m_objectCollection -> Add(projectile);
}