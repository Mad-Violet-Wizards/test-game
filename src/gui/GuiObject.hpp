#pragma once

#include "GuiAlign.hpp"
#include "GuiMargin.hpp"

class GuiObject : public sf::Drawable, public sf::Transformable
{

public:

  GuiObject(Window* window);
  virtual ~GuiObject();

  virtual void Update(float deltaTime) {}
  virtual sf::FloatRect GetSize() { return sf::FloatRect{}; }

  virtual void SetPosition(const float x, const float y);
  virtual void SetPosition(const sf::Vector2f &position);
  const sf::Vector2f &GetPosition();

  //
  // Margin section.
  //

  GuiMargin &GetMargin();

  //
  // End of margin section.
  //


  //
  // Align section.
  //

  void SetAlign(GuiAlign align);
  GuiAlign GetAlign();

  //
  // End of align section.
  //

  void SetVisible(bool visible);

  void SetMouseTracking(bool mouseTracking);

protected:

  Window *m_window;

  GuiMargin m_margins;
  GuiAlign m_align;

  sf::Vector2f m_position;

  bool m_visible;
  bool m_mouseTracking;

private:

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  sf::RectangleShape m_testRect;

};
