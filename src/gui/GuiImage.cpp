#include "GuiImage.hpp"


GuiImage::GuiImage(Window *window)
  : GuiObject(window) { }

GuiImage::~GuiImage() { }

void GuiImage::Update(float deltaTime)
{

}

void GuiImage::LoadImage(const std::string &name)
{
  m_image = AssetsStorage::GetInstance().GetImage(name);

  sf::IntRect area(0, 0, m_image.getSize().x, m_image.getSize().y);

  if (area.width > m_window -> GetWindowSize().x)
  {
    FILE_LOG_WARNING("debug.txt", "[GuiImage][LoadImage] Image width is higher that current Window size, it might cause problems with correct layout placements");
  }

  if (area.height > m_window -> GetWindowSize().y)
  {
    FILE_LOG_WARNING("debug.txt", "[GuiImage][LoadImage] Image height is higher that current Window size, it might cause problems with correct layout placements");
  }

  if (!m_texture.loadFromImage(m_image, area))
  {
    FILE_LOG_ERROR("debug.txt", "[GuiImage][LoadImage] Cannot create texture from image.\n");

    return;
  }

  m_sprite.setTexture(m_texture);
}

void GuiImage::LoadImageFromFilePath(const std::string &filePath)
{
  if (!m_image.loadFromFile(filePath))
  {
    FILE_LOG_ERROR("debug.txt", "[GuiImage][LoadImageFromFilePath] Cannot load image from file path.\n");

    return;
  }
  sf::IntRect area(0, 0, m_image.getSize().x, m_image.getSize().y);

  if (area.width > m_window -> GetWindowSize().x)
  {
    FILE_LOG_WARNING("debug.txt", "[GuiImage][LoadImageFromFilePath] Image width is higher that current Window size, it might cause problems with correct layout placements");
  }

  if (area.height > m_window -> GetWindowSize().y)
  {
    FILE_LOG_WARNING("debug.txt", "[GuiImage][LoadImageFromFilePath] Image height is higher that current Window size, it might cause problems with correct layout placements");
  }

  if (!m_texture.loadFromImage(m_image, area))
  {
    FILE_LOG_ERROR("debug.txt", "[GuiImage][LoadImageFromFilePath] Cannot create texture from image.\n");

    return;
  }

  m_sprite.setTexture(m_texture);
}

sf::FloatRect GuiImage::GetSize()
{
  return m_sprite.getGlobalBounds();
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