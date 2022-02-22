#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <list>

#include "GuiObject.hpp"
#include "Window.hpp"

class GuiLayout
{
public:

  GuiLayout(Window *window);
  ~GuiLayout();


  void Update();
  void Draw(Window &window);

  /*
  * TODO: Think, if those are really important here, GuiLayout is only a base class containg basic informations.
  */

  virtual void AddWidget(std::shared_ptr<GuiObject> widget);
  virtual void RemoveWidget(std::shared_ptr<GuiObject> widget); // Made this method virtual only for some unknown time.

  void SetVisible(bool state);
  /*
  * FIXME: Those four methods are using the same code, maybe move it to one mehtod "CountRelative"?
  */
  virtual void SetRelativeSize(const unsigned int x, const unsigned int y);
  virtual void SetRelativeSize(const sf::Vector2u &size);
  virtual void SetRelativePosition(const unsigned int x, const unsigned int y);
  virtual void SetRelativePosition(const sf::Vector2u &position);

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
