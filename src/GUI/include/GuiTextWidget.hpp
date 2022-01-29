#pragma once

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "GuiObject.hpp"

class GuiTextWidget : public GuiObject
{
public:

  GuiTextWidget(Window* window);
  ~GuiTextWidget();

  void Update() override;
  sf::FloatRect GetSize() override;

  void SetPosition(const float x, const float y) override;
  void SetPosition(const sf::Vector2f &position) override;

  void SetCharacterSize(const int size);
  void SetText(const std::string &text);
  void SetText(const char *text);

  void SetColor(const int r, const int g, const int b);
  void SetColor(const sf::Color &color);

private:

  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

  sf::Font m_font;
  sf::Text m_text;
};