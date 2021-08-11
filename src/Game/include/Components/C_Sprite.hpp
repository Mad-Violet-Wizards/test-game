#pragma once

#include "Object.hpp"
#include "Components/Component.hpp"
#include "Components/C_Transform.hpp"

class C_Sprite : public Component
{
  public:

    C_Sprite(Object* owner);

    void Load(const std::string& filePath);

    void Update(float deltaTime) override;

    void Draw(Window& window) override;

  private:

    sf::Texture m_texture;
    sf::Sprite m_sprite;
};
