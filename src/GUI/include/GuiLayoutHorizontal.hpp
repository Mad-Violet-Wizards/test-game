#pragma once

#include "GuiLayout.hpp"
#include "Window.hpp"


class GuiLayoutHorizontal : public GuiLayout
{
public:

  GuiLayoutHorizontal(Window *window);
  ~GuiLayoutHorizontal();

  void AddWidget(std::shared_ptr<GuiObject> widget) override;

  void SetRelativeSize(const unsigned int x, const unsigned int y) override;
  void SetRelativeSize(const sf::Vector2u &size) override;
  void SetRelativePosition(const unsigned int x, const unsigned int y) override;
  void SetRelativePosition(const sf::Vector2u &position) override;

  /*
  TODO: Consider moving it to private member.
  */
  void CheckToUpdateSize();

private:

  void UpdatePositionOfWidget(std::shared_ptr<GuiObject> widget);
  sf::Vector2f m_cursor;
};