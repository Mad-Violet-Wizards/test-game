#pragma once

#include <SFML/Graphics.hpp>

#include "GuiWidget.hpp"

class GuiTextWidget : public GuiWidget
{
  public:

    GuiTextWidget();
    ~GuiTextWidget();

    void Update() override;

    void SetCharacterSize(const int size);
    void SetString(const std::string& string);

    void SetColor(const int r, const int g, const int b);
    void SetColor(const sf::Color& color);

    void SetPosition(const sf::Vector2f& position);
    void SetPosition(float x, float y);

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::Font m_font;
    sf::Text m_text;
};