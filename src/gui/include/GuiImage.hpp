#pragma once

#include <SFML/Graphics.hpp>

#include "GuiObject.hpp"
#include "Window.hpp"

class GuiImage : public GuiObject
{

public:

  GuiImage(Window *window);
  ~GuiImage();

  void Update(float deltaTime) override;

  void LoadImage(const std::string &name);
  void LoadImageFromFilePath(const std::string &filePath);

  sf::FloatRect GetSize() override;

  void SetPosition(const float x, const float y) override;
  void SetPosition(const sf::Vector2f &position) override;

private:

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:

  //
  // Maybe move to struct?
  //

  sf::Image   m_image;

  sf::Sprite  m_sprite;
  sf::Texture m_texture;

};