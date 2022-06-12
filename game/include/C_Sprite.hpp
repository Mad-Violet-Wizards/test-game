#pragma once

#include "Object.hpp"
#include "Component.hpp"
#include "C_Transform.hpp"

class C_Sprite : public Component
{

public:

  C_Sprite(Object *owner);

  void Load(const sf::Texture &texture);

  void Update(float deltaTime) override;
  void Draw(Window &window) override;

private:

  sf::Sprite m_sprite;

};
