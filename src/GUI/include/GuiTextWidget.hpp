#pragma once

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "GuiWidget.hpp"

class GuiTextWidget : public GuiWidget
{
  public:

    GuiTextWidget(Window* window);
    ~GuiTextWidget();

    void Update();

  protected:

    void SetCharacterSize(const int size);
    void SetString(const std::string& string);

    void SetColor(const int r, const int g, const int b);
    void SetColor(const sf::Color& color);

    void SetAbsolutePosition(const sf::Vector2f& position);
    void SetAbsolutePosition(float x, float y);

    void SetRelativePosition(const std::string &x, const std::string &y) override;
    void SetRelativePosition(const char *x, const char *y) override;
    void SetRelativePosition(const int x, const int y) override;

  private:

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Font m_font;
    sf::Text m_text;
};