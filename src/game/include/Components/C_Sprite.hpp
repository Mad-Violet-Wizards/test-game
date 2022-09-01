#pragma once

#include "Object.hpp"
#include "Component.hpp"
#include "C_Transform.hpp"

class C_Sprite : public Component
{

public:

  C_Sprite(Object *owner);

  void Load(const sf::Texture &texture);
  void Load(std::shared_ptr<sf::Texture> texture);

  void Update(float deltaTime) override;
  void Draw(Window &window) override;

  void SetTextureRect(int x, int y, int width, int height);
  void SetTextureRect(const sf::IntRect &rect);
  void SetScale(float x, float y);

private:

  sf::Sprite m_sprite;

};
