#include <iostream>

#include "Log.hpp"
#include "GuiLayoutHorizontal.hpp"

GuiLayoutHorizontal::GuiLayoutHorizontal(Window *window)
  : GuiLayout(window)
{
}

GuiLayoutHorizontal::~GuiLayoutHorizontal()
{
}

void GuiLayoutHorizontal::AddWidget(std::shared_ptr<GuiObject> widget)
{
  m_widgets.push_back(widget);

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

void GuiLayoutHorizontal::RemoveWidget(std::shared_ptr<GuiObject> widget)
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

void GuiLayoutHorizontal::SetRelativeSize(unsigned int x, unsigned int y)
{
  GuiLayout::SetRelativeSize(x, y);
}

void GuiLayoutHorizontal::SetRelativeSize(const sf::Vector2u &size)
{
  GuiLayout::SetRelativeSize(size);
}

void GuiLayoutHorizontal::SetRelativePosition(unsigned int x, unsigned int y)
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


void GuiLayoutHorizontal::SetRelativePosition(const sf::Vector2u &position)
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

void GuiLayoutHorizontal::CheckToUpdateSize()
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

void GuiLayoutHorizontal::UpdatePositionOfWidget(std::shared_ptr<GuiObject> widget)
{
  GuiObject::GuiAlign align = widget -> GetAlign();

  switch (align)
  {
    case GuiObject::GuiAlign::AlignTop:
    {
      sf::FloatRect widgetSize = widget -> GetSize();

      m_cursor.x += widget -> GetMargin().GetLeftMargin();
      sf::Vector2f top = { m_position.x + m_cursor.x, m_position.y };

      sf::Vector2f position = { top.x, top.y };
      widget -> SetPosition(position);

      m_cursor.x += widget -> GetSize().width +
                    widget -> GetMargin().GetRightMargin();
      break;
    }
    case GuiObject::GuiAlign::AlignRight:
    {
      LOG_WARNING("[GuiLayoutHorizontal][UpdatePositionOfWidget] AlignRight is not supported in this layout.");

      throw std::logic_error("[Error][GuiLayoutHorizontal][UpdatePositionOfWidget] AlignRight is not supported. Maybe you want to use GuiLayoutVertical instead?\n");
      break;
    }
    case GuiObject::GuiAlign::AlignCenter:
    {
      auto w = FindWidgetWithHighestHeight();

      if (w != nullptr)
      {
        sf::FloatRect widgetSize = w -> GetSize();

        widgetSize.height /= 2;

        m_cursor.x += widget -> GetMargin().GetLeftMargin();
        sf::Vector2f center = { m_cursor.x, m_position.y + m_size.y / 2 };

        sf::Vector2f position = { center.x, center.y - widgetSize.height };
        widget -> SetPosition(position);

        m_cursor.x += widget -> GetSize().width +
                      widget -> GetMargin().GetRightMargin();
      }
      else
      {
        throw std::logic_error("[Error][GuiLayoutHorizontal][UpdatePositionOfWidget] Didn't found widget with highest height.\n");
      }

      break;
    }
    case GuiObject::GuiAlign::AlignBottom:
    {
      auto w = FindWidgetWithHighestHeight();

      if (w != nullptr)
      {
        sf::FloatRect widgetSize = w -> GetSize();

        m_cursor.x += widget -> GetMargin().GetLeftMargin();
        sf::Vector2f bottom = { m_position.x + m_cursor.x, m_position.y + m_size.y };

        sf::Vector2f position = { bottom.x, bottom.y - widgetSize.height / 2 };
        widget -> SetPosition(position);

        m_cursor.x += widget -> GetSize().width +
                      widget -> GetMargin().GetRightMargin();
      }
      else
      {
        throw std::logic_error("[Error][GuiLayoutHorizontal][UpdatePositionOfWidget] Didn't found widget with highest height.\n");
      }
      break;
    }
    case GuiObject::GuiAlign::AlignLeft:
    {
      LOG_WARNING("[GuiLayoutHorizontal][UpdatePositionOfWidget] AlignLeft is not supported in this layout.");

      throw std::logic_error("[Error][GuiLayoutHorizontal][UpdatePositionOfWidget] AlignLeft is not supported. Maybe you want to use GuiLayoutVertical instead?\n");
      break;
    }
    default:
    {
      break;
    }
  }
}
