#pragma once

#include <map>

#include "GuiLayout.hpp"

#include "Window.hpp"

class GuiLayoutTable : public GuiLayout
{

public:

  // First value is row, second value is column.

  using Key = std::pair<int, int>;

  GuiLayoutTable(Window *window);
  ~GuiLayoutTable();

  void Update(float deltaTime) override;
  void Draw(Window &window) override;

  void AddWidget(std::shared_ptr<GuiObject> widget, int row, int column);
  void RemoveWidget(std::shared_ptr<GuiObject>);

  void SetRelativeSize(unsigned int x, unsigned int y) override;
  void SetRelativeSize(const sf::Vector2u &size) override;
  void SetRelativePosition(unsigned int x, unsigned int y) override;
  void SetRelativePosition(const sf::Vector2u &position) override;


private:

  void UpdatePositionOfWidget(std::shared_ptr<GuiObject> widget, int row, int column);

  std::multimap<Key, std::shared_ptr<GuiObject>> m_widgets;

  sf::Vector2f m_scalingFactor;

};