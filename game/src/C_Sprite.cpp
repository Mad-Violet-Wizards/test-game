#include "C_Sprite.hpp"

C_Sprite::C_Sprite(Object *owner) : Component(owner) {}

void C_Sprite::Load(const std::string &filePath)
{
  m_texture.loadFromFile(filePath);
  m_sprite.setTexture(m_texture);
}

void C_Sprite::Update(float deltaTime)
{
  m_sprite.setPosition(m_owner->GetComponent<C_Transform>()->GetPosition());
}

void C_Sprite::Draw(Window &window)
{
  window.Draw(m_sprite);
}