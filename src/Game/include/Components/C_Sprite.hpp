#pragma once

#include "Components/Component.hpp"

class C_Sprite : public Component
{
  public:

    C_Sprite(Object* owner);

    void Load(const std::string& filePath);

    void Draw(Window& window) override;

  private:

    sf::Texture m_texture;
    sf::Sprite m_sprite;
};
