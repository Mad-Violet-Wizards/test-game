#include "C_Sprite.hpp"

#include "Log.hpp"

C_Sprite::C_Sprite(Object *owner) : Component(owner) {}

void C_Sprite::Load(const sf::Texture &texture)
{
  m_sprite.setTexture(texture);
}

void C_Sprite::Load(std::shared_ptr<sf::Texture> texture)
{
  m_sprite.setTexture(*texture);
}

void C_Sprite::Update(float deltaTime)
{
  m_sprite.setPosition(m_owner -> GetComponent<C_Transform>() -> GetPosition());
}

void C_Sprite::Draw(Window &window)
{
  window.Draw(m_sprite);
}

void C_Sprite::SetTextureRect(int x, int y, int width, int height)
{
  m_sprite.setTextureRect({ x, y, width, height });
}

void C_Sprite::SetTextureRect(const sf::IntRect &rect)
{
  m_sprite.setTextureRect(rect);
}

void C_Sprite::SetScale(float x, float y)
{
  m_sprite.setScale(x, y);
}