#pragma once

#include <SFML/Graphics.hpp>

#include "GuiWidget.hpp"

class GuiTextWidget : public GuiWidget
{
  public:

    GuiTextWidget();
    ~GuiTextWidget();

  private:
  
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Font m_font;
    sf::Text m_text;
};