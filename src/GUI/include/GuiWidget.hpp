#pragma once

#include <SFML/Graphics.hpp>
#include "Window.hpp"

class GuiWidget : public sf::Drawable, public sf::Transformable
{

  public:

    GuiWidget();
    ~GuiWidget();

    virtual void Update() {};

  private:
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::RectangleShape m_testRect;
};