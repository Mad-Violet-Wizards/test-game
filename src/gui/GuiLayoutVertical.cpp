#include <iostream>

#include "GuiAlign.hpp"
#include "GuiLayoutVertical.hpp"

GuiLayoutVertical::GuiLayoutVertical(Window *window)
  : GuiLayout(window)
{
}

GuiLayoutVertical::~GuiLayoutVertical()
{
}

void GuiLayoutVertical::AddWidget(std::shared_ptr<GuiObject> widget)
{
  m_widgets.push_back(widget);

  UpdatePositionOfWidget(widget);
  
  CheckToUpdateSize();
}

void GuiLayoutVertical::RemoveWidget(std::shared_ptr<GuiObject> widget)
{
  m_widgets.remove(widget);

  /*
  FIXME: This is defienietly not the best way to do it.
  */

  m_cursor = m_position;

  for (auto widget : m_widgets)
  {
    UpdatePositionOfWidget(widget);
  }

  CheckToUpdateSize();
}

void GuiLayoutVertical::SetRelativeSize(unsigned int x, unsigned int y)
{
  GuiLayout::SetRelativeSize(x, y);
}

void GuiLayoutVertical::SetRelativeSize(const sf::Vector2u &size)
{
  GuiLayout::SetRelativeSize(size);
}

void GuiLayoutVertical::SetRelativePosition(unsigned int x, unsigned int y)
{
  GuiLayout::SetRelativePosition(x, y);
  m_cursor = m_position;

  if (m_widgets.size() != 0)
  {
    for (auto widget : m_widgets)
    {
      UpdatePositionOfWidget(widget);
    }
  }
}


void GuiLayoutVertical::SetRelativePosition(const sf::Vector2u &position)
{
  GuiLayout::SetRelativePosition(position);
  m_cursor = m_position;

  if (m_widgets.size() != 0)
  {
    for (auto widget : m_widgets)
    {
      UpdatePositionOfWidget(widget);
    }
  }
}

void GuiLayoutVertical::CheckToUpdateSize()
{
  float height = 0;

  // Acumulate the height of widgets.
  for (auto &widget : m_widgets)
  {
    height += widget -> GetSize().height +
              widget -> GetMargin().GetBottomMargin() +
              widget -> GetMargin().GetTopMargin();
  }
  
  // If accumulated height of widgets is higher than actual layout height, resize.
  if (height > m_size.y)
  {
    m_size.y = height;

    SetRelativeSize(ScaleWindowAbsoluteToRelative(m_size));
  }

  // If the width of layout is smaller than widest widget in it, resize.
  auto w = FindWidgetWithHighestWidth();

  // If the layout size is not correct, then resize it correctly to according data.
  if (w != nullptr && w -> GetSize().width > m_size.x)
  {
    m_size.x = w -> GetSize().width +
               w -> GetMargin().GetLeftMargin() +
               w -> GetMargin().GetRightMargin();

    // We've to restart cursor, 
    // because new size have to 
    // recalculate the responsive location 
    // of every widget.
    
    m_cursor = m_position;

    for (auto widget : m_widgets)
    {
      UpdatePositionOfWidget(widget);
    }

    SetRelativeSize(ScaleWindowAbsoluteToRelative(m_size));
  }
}

void GuiLayoutVertical::RefreshSize()
{
  SetRelativeSize(m_relativeSize);
  SetRelativePosition(m_relativePosition);
}

void GuiLayoutVertical::UpdatePositionOfWidget(std::shared_ptr<GuiObject> widget)
{
  GuiAlign align = widget -> GetAlign();

  switch (align)
  {
    case GuiAlign::AlignTop:
    {
      FILE_LOG_WARNING("debug.txt", "[GuiLayoutVertical][UpdatePositionOfWidget] AlignTop is not supported in this layout.");

      break;
    }
    case GuiAlign::AlignRight:
    {
      sf::FloatRect widgetSize = widget -> GetSize();

      // Increase current currsor y position to include top margin.
      m_cursor.y += widget -> GetMargin().GetTopMargin();
      sf::Vector2f right = { m_position.x + m_size.x, m_cursor.y };

      sf::Vector2f position = { right.x - widgetSize.width, right.y };
      widget -> SetPosition(position);

      // Move cursor to the next row.
      m_cursor.y += widget -> GetSize().height +
                    widget -> GetMargin().GetBottomMargin();
      break;
    }
    case GuiAlign::AlignCenter:
    {
      sf::FloatRect widgetSize = widget -> GetSize();

      // We got center pixel.
      widgetSize.width /= 2;

      // Increase current currsor y position to include top margin.
      m_cursor.y += widget -> GetMargin().GetTopMargin();
      sf::Vector2f center = { m_position.x + m_size.x / 2, m_cursor.y };

      sf::Vector2f position = { center.x - widgetSize.width, center.y };
      widget -> SetPosition(position);

      // Move cursor to the next row.
      m_cursor.y += widget -> GetSize().height +
                    widget -> GetMargin().GetBottomMargin();
      break;
    }
    case GuiAlign::AlignBottom:
    {
      FILE_LOG_WARNING("debug.txt", "[GuiLayoutVertical][UpdatePositionOfWidget] AlignBottom is not supported in this layout.");

      break;
    }
    case GuiAlign::AlignLeft:
    {
      // Increase current currsor y position to include top margin.
      m_cursor.y += widget -> GetMargin().GetTopMargin();
      sf::Vector2f left = { m_position.x, m_cursor.y };

      sf::Vector2f position = { left.x, left.y };
      widget -> SetPosition(position);

      // Move cursor to the next row.
      m_cursor.y += widget -> GetSize().height +
                    widget -> GetMargin().GetBottomMargin();
      break;
    }
    default:
    {
      break;
    }
  }
}
