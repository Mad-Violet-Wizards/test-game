#include "GuiImage.hpp"

GuiImage::GuiImage(Window *window)
  : GuiObject(window) { }

GuiImage::~GuiImage() { }

void GuiImage::Update(float deltaTime)
{

}

void GuiImage::LoadImage(const std::string &name)
{

}

sf::FloatRect GuiImage::GetSize()
{
  return sf::FloatRect(m_position.x, m_position.y, m_image.getSize().x, m_image.getSize().y);
}

void GuiImage::SetPosition(const float x, const float y)
{
  GuiObject::SetPosition(x, y);
  m_sprite.setPosition(m_position);
}

void GuiImage::SetPosition(const sf::Vector2f &position)
{
  GuiObject::SetPosition(position);
  m_sprite.setPosition(m_position);
}

void GuiImage::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
  states.transform *= getTransform();
  target.draw(m_sprite, states);
}