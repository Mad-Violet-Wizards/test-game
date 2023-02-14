#pragma once

#include "GuiObject.hpp"

class GuiLayout
{

public:

  GuiLayout(Window *window);
  virtual ~GuiLayout();

  virtual void Update(float deltaTime);
  virtual void Draw(Window &window);

  void SetVisible(bool visible);
  /*
  * FIXME: Those four methods are using the same code, maybe move it to one mehtod "CountRelative"?
  */
  virtual void SetRelativeSize(unsigned int x, unsigned int y);
  virtual void SetRelativeSize(const sf::Vector2u &size);
  virtual void SetRelativePosition(unsigned int x, unsigned int y);
  virtual void SetRelativePosition(const sf::Vector2u &position);

  const sf::Vector2f GetSize()             const { return m_size; }
  const sf::Vector2u GetRelativeSize()     const { return m_relativeSize; }
  const sf::Vector2f GetPosition()         const { return m_position; }
  const sf::Vector2u GetRelativePosition() const { return m_relativePosition; }


  virtual void RefreshSize() {};

  std::shared_ptr<GuiObject> FindWidgetWithSmallestWidth();
  std::shared_ptr<GuiObject> FindWidgetWithHighestWidth();
  std::shared_ptr<GuiObject> FindWidgetWithSmallestHeight();
  std::shared_ptr<GuiObject> FindWidgetWithHighestHeight();

protected:

  sf::Vector2f m_size;
  sf::Vector2u m_relativeSize;
  sf::Vector2f m_position;
  sf::Vector2u m_relativePosition;

  std::list<std::shared_ptr<GuiObject>> m_widgets;
  bool m_isVisible;

  const sf::Vector2f ScaleRelativeToWindowAbsolute(const sf::Vector2u &proportions);
  const sf::Vector2u ScaleWindowAbsoluteToRelative(const sf::Vector2f &values);

private:

  Window *m_window;

};
