#pragma once

#include "GuiLayout.hpp"

#include "Window.hpp"

class GuiLayoutHorizontal : public GuiLayout
{

public:

  GuiLayoutHorizontal(Window *window);
  ~GuiLayoutHorizontal();

  void AddWidget(std::shared_ptr<GuiObject> widget);

  void SetRelativeSize(unsigned int x, unsigned int y) override;
  void SetRelativeSize(const sf::Vector2u &size) override;
  void SetRelativePosition(unsigned int x, unsigned int y) override;
  void SetRelativePosition(const sf::Vector2u &position) override;

private:

  void UpdatePositionOfWidget(std::shared_ptr<GuiObject> widget);

  void CheckToUpdateSize();

  sf::Vector2f m_cursor;

};
