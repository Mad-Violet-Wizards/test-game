#include <iostream>

#include "GuiLayoutVertical.hpp"

GuiLayoutVertical::GuiLayoutVertical(Window *window)
  : GuiLayout(window)
{
  std::cout << "[Info][GuiLayoutVertical] Created GuiLayoutVertical.\n";
}

GuiLayoutVertical::~GuiLayoutVertical()
{
  std::cout << "[Info][GuiLayoutVertical] Destroyed GuiLayoutVertical.\n";
}

void GuiLayoutVertical::AddWidget(std::shared_ptr<GuiObject> widget)
{
  std::cout << "[Info][GuiLayoutVertical] Added new widget to GuiLayoutVertical.\n";
  m_widgets.push_back(widget);

  UpdatePositionOfWidget(widget);
  
  CheckToUpdateSize();
}

void GuiLayoutVertical::SetRelativeSize(const unsigned int x, const unsigned int y)
{
  GuiLayout::SetRelativeSize(x, y);
}

void GuiLayoutVertical::SetRelativeSize(const sf::Vector2u &size)
{
  GuiLayout::SetRelativeSize(size);
}

void GuiLayoutVertical::SetRelativePosition(const unsigned int x, const unsigned int y)
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
    height += widget -> GetSize().height + widget -> GetBottomMargin() + widget -> GetTopMargin();
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
    m_size.x = w -> GetSize().width + w -> GetLeftMargin() + w -> GetRightMargin();

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
  GuiObject::GuiAlign align = widget -> GetAlign();

  switch (align)
  {
    case GuiObject::GuiAlign::AlignTop:
    {
      std::cout << "[Info][GuiLayoutVertical][UpdatePositionOfWidget] Detected AlignTop.\n";
      throw std::logic_error("[Error][GuiLayoutVertical][UpdatePositionOfWidget] AlignTop is not supported. Maybe you want to use GuiLayoutHorizontal instead?\n");
      break;
    }
    case GuiObject::GuiAlign::AlignRight:
    {
      std::cout << "[Info][GuiLayoutVertical][UpdatePositionOfWidget] Detected AlignRight.\n";
      sf::FloatRect widgetSize = widget -> GetSize();

      // Increase current currsor y position to include top margin.
      m_cursor.y += widget -> GetTopMargin();
      sf::Vector2f right = { m_position.x + m_size.x, m_cursor.y };

      sf::Vector2f position = { right.x - widgetSize.width, right.y };
      widget -> SetPosition(position);

      // Move cursor to the next row.
      m_cursor.y += widget -> GetSize().height + widget -> GetBottomMargin();
      break;
    }
    case GuiObject::GuiAlign::AlignCenter:
    {
      std::cout << "[Info][GuiLayoutVertical][UpdatePositionOfWidget] Detected AlignCenter.\n";
      sf::FloatRect widgetSize = widget -> GetSize();

      // We got center pixel.
      widgetSize.width /= 2;

      // Increase current currsor y position to include top margin.
      m_cursor.y += widget -> GetTopMargin();
      sf::Vector2f center = { m_position.x + m_size.x / 2, m_cursor.y };

      sf::Vector2f position = { center.x - widgetSize.width, center.y };
      widget -> SetPosition(position);

      // Move cursor to the next row.
      m_cursor.y += widget -> GetSize().height + widget -> GetBottomMargin();
      break;
    }
    case GuiObject::GuiAlign::AlignBottom:
    {
      std::cout << "[Info][GuiLayoutVertical][UpdatePositionOfWidget] Detected AlignBottom.\n";
      throw std::logic_error("[Error][GuiLayoutVertical][UpdatePositionOfWidget] AlignBottom is not supported. Maybe you want to use GuiLayoutHorizontal instead?\n");
      break;
    }
    case GuiObject::GuiAlign::AlignLeft:
    {
      std::cout << "[Info][GuiLayoutVertical][UpdatePositionOfWidget] Detected AlignLeft.\n";
      // Increase current currsor y position to include top margin.
      m_cursor.y += widget -> GetTopMargin();
      sf::Vector2f left = { m_position.x, m_cursor.y };

      sf::Vector2f position = { left.x, left.y };
      widget -> SetPosition(position);

      // Move cursor to the next row.
      m_cursor.y += widget -> GetSize().height + widget -> GetBottomMargin();
      break;
    }
    default:
    {
      break;
    }
  }
}
