#include <iostream>

#include "GuiLayoutTable.hpp"

GuiLayoutTable::GuiLayoutTable(Window *window) 
  : GuiLayout(window)
{
  std::cout << "[Info][GuiLayoutTable] Created GuiLayoutTable.\n";
}

GuiLayoutTable::~GuiLayoutTable()
{
  std::cout << "[Info][GuiLayoutTable] Destroyed GuiLayoutTable.\n";
}

void GuiLayoutTable::Update()
{
  if (m_isVisible)
  {
    for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
    {
      it -> second -> Update();
    }
  }
}

void GuiLayoutTable::Draw(Window &window)
{
  if (m_isVisible)
  {
    for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
    {
      window.Draw(*static_cast<sf::Drawable*>(it -> second.get()));
    }
  }
}

void GuiLayoutTable::AddWidget(std::shared_ptr<GuiObject> widget, int row, int column)
{
  std::cout << "[Info][GuiLayoutTable] Added new widget to GuiLayoutTable.\n";

  Key k = { row, column };

  m_widgets.insert( { k, widget } );

  if (widget -> GetSize().width > m_scalingFactor.x)
  {
    m_scalingFactor.x = widget -> GetSize().width;

    if (m_widgets.size() > 1)
    {
       for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
       {
          int row, count;
          std::tie(row, count) = it -> first;

          UpdatePositionOfWidget(it -> second, row, count);
        }
    }
  }

  if (widget -> GetSize().height > m_scalingFactor.y)
  {
    m_scalingFactor.y = widget -> GetSize().height;

    if (m_widgets.size() > 1)
    {
       for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
       {
          int row, count;
          std::tie(row, count) = it -> first;

          UpdatePositionOfWidget(it -> second, row, count);
        }
    }  
  }

  UpdatePositionOfWidget(widget, row, column);
}

void GuiLayoutTable::RemoveWidget(std::shared_ptr<GuiObject> widget)
{

  // Find widget and remove it.

 for (auto it = m_widgets.begin(); it != m_widgets.end(); ++it)
  {
    if (it -> second == widget)
    {
      m_widgets.erase(it -> first);
    }
  }

  // There might be a chance that removed widget was setup to be scaling factor.
  // If it was - update scalingFactor.

  if (m_widgets.size() > 1)
  {
    for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
    {
      if (it -> second -> GetSize().width > m_scalingFactor.x)
      {
        m_scalingFactor.x = it -> second -> GetSize().width;
      }

      if (it -> second -> GetSize().height > m_scalingFactor.y)
      {
        m_scalingFactor.y = it -> second -> GetSize().height;
      }
    }
  }

  // Update position of layout according to new scaling factor.

  if (m_widgets.size() > 1)
  {
    for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
    {
      int row, count;
      std::tie(row, count) = it -> first;

      UpdatePositionOfWidget(it -> second, row, count);
    }
  }
}

void GuiLayoutTable::SetRelativeSize(unsigned int x, unsigned int y)
{
  GuiLayout::SetRelativeSize(x, y);
}

void GuiLayoutTable::SetRelativeSize(const sf::Vector2u &size)
{
  GuiLayout::SetRelativeSize(size);
}

void GuiLayoutTable::SetRelativePosition(unsigned int x, unsigned int y)
{
  GuiLayout::SetRelativePosition(x, y);

  if (m_widgets.empty() == false)
  {
    for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
    {
      int row, count;
      std::tie(row, count) = it -> first;

      UpdatePositionOfWidget(it -> second, row, count);
    }
  }
}


void GuiLayoutTable::SetRelativePosition(const sf::Vector2u &position)
{
  GuiLayout::SetRelativePosition(position);

  if (m_widgets.empty() == false)
  {
    for (auto it = m_widgets.cbegin(); it != m_widgets.cend(); ++it)
    {
      int row, count;
      std::tie(row, count) = it -> first;

      UpdatePositionOfWidget(it -> second, row, count);
    }
  }
}

void GuiLayoutTable::UpdatePositionOfWidget(std::shared_ptr<GuiObject> widget, int row, int column)
{
  sf::Vector2f position = { m_position.x + (m_scalingFactor.x * row),
                            m_position.y + (m_scalingFactor.y * column) };

  position.x += widget -> GetMargin().GetLeftMargin() * row;
  position.y += widget -> GetMargin().GetTopMargin()  * column;

  widget -> SetPosition(position);
}