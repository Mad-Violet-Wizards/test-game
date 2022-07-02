#pragma once

#include "GuiLayout.hpp"
#include "Window.hpp"

class GuiLayoutVertical : public GuiLayout
{

public:

  /*
  TODO: Add flag Flag::Expanding that will allow to expand depending on size of widgets inside.
  */

  GuiLayoutVertical(Window *window);
  ~GuiLayoutVertical();

  void AddWidget(std::shared_ptr<GuiObject> widget);

  void SetRelativeSize(unsigned int x, unsigned int y) override;
  void SetRelativeSize(const sf::Vector2u &size) override;
  void SetRelativePosition(unsigned int x, unsigned int y) override;
  void SetRelativePosition(const sf::Vector2u &position) override;

  //
  // Signal & slots.
  //

  void RefreshSize() override;

private:

  void UpdatePositionOfWidget(std::shared_ptr<GuiObject> widget);

  void CheckToUpdateSize();

  sf::Vector2f m_cursor;

};
