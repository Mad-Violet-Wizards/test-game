#pragma once

#include <SFML/Graphics.hpp>

#include "Window.hpp"
#include "Input.hpp"

class GuiObject : public sf::Drawable, public sf::Transformable
{
public:

  typedef struct
  {
    float top;
    float right;
    float bottom;
    float left;
  } GuiMargins;

  enum class GuiAlign
  {
    AlignTop,
    AlignRight,
    AlignCenter,
    AlignBottom,
    AlignLeft
  };

  GuiObject(Window* window);
  ~GuiObject();

  virtual void Update() {}
  virtual sf::FloatRect GetSize() { return sf::FloatRect{}; }

  virtual void SetPosition(const float x, const float y);
  virtual void SetPosition(const sf::Vector2f &position);
  const sf::Vector2f &GetPosition();

  //
  // Align section.
  //

  void SetTopMargin(const float topMargin);
  void SetRightMargin(const float rightMargin);
  void SetBottomMargin(const float bottomMargin);
  void SetLeftMargin(const float leftMargin);
  void GetMargins(float &topMargin, float &rightMargin, float &bottomMargin, float &leftMargin);
  GuiMargins GetMargins();
  float GetTopMargin() const;
  float GetRightMargin() const;
  float GetBottomMargin() const;
  float GetLeftMargin() const;

  void SetAlign(GuiAlign align);
  GuiAlign GetAlign();

  //
  // End of align section.
  //

  void SetInput(Input *input);


protected:

  Window *m_window;
  Input *m_input;

  GuiMargins m_margins;
  GuiAlign m_align;
  sf::Vector2f m_position;

private:

  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
  sf::RectangleShape m_testRect;
};