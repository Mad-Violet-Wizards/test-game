#pragma once

#include "GuiObject.hpp"
#include "GuiMargin.hpp"

class GuiTextWidget : public GuiObject
{

public:

  GuiTextWidget(Window *window);
  ~GuiTextWidget();

  void Update(float deltaTime) override;
  sf::FloatRect GetSize() override;

  void SetPosition(const float x, const float y) override;
  void SetPosition(const sf::Vector2f &position) override;

  void SetCharacterSize(const int size);
  void SetText(const std::string &text);
  void SetText(const char *text);

  void SetColor(const int r, const int g, const int b);
  void SetColor(const sf::Color &color);

  void SetHoverCapture(bool enabled);

  void SetHoverColor(const int r, const int g, const int b);
  void SetHoverColor(const sf::Color &color);

  //
  // Signal & Slots
  //

  boost::signals2::signal<void()> Clicked;

private:

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

  sf::Font m_font;
  sf::Text m_text;

  sf::Color m_color;
  sf::Color m_hoverColor;

  bool m_hoverEffect;

};