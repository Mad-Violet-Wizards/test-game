#include <iostream>

#include "GuiLayout.hpp"

GuiLayout::GuiLayout(Window *window)
  : m_window(window),
  m_isVisible(true),
  m_size(sf::Vector2f{ 100, 100 }),
  m_position(sf::Vector2f{ 0, 0 })
{
  std::cout << "[Info][GuiLayout] Created new Gui Layout\n";
}

GuiLayout::~GuiLayout()
{
  std::cout << "[Info][GuiLayout] Destroyed Gui Layout\n";
}

void GuiLayout::Update()
{
  if (m_isVisible)
  {
    for (auto &widget : m_widgets)
    {
      widget -> Update();
    }
  }
}

void GuiLayout::Draw(Window &window)
{
  if (m_isVisible)
  {
    for (auto &widget : m_widgets)
    {
      window.Draw(*static_cast<sf::Drawable*>(widget.get()));
    }
  }
}

void GuiLayout::AddWidget(std::shared_ptr<GuiObject> widget)
{
  m_widgets.push_back(widget);
}

void GuiLayout::RemoveWidget(std::shared_ptr<GuiObject> widget)
{
  // TODO: Simple, but works, maybe evalute it to something better?
  for (auto w : m_widgets)
  {
    if (w == widget)
    {
      m_widgets.remove(widget);
      break;
    }
  }
}

void GuiLayout::SetVisible(bool visible)
{
  m_isVisible = visible;
}

void GuiLayout::SetRelativeSize(const unsigned int x, const unsigned int y)
{
  m_size = ScaleRelativeToWindowAbsolute(sf::Vector2u {x, y} );
  m_relativeSize = sf::Vector2u{ x, y };
}

void GuiLayout::SetRelativeSize(const sf::Vector2u &size)
{
  m_size = ScaleRelativeToWindowAbsolute(size);
  m_relativeSize = size;
}

void GuiLayout::SetRelativePosition(const unsigned int x, const unsigned int y)
{
  m_position = ScaleRelativeToWindowAbsolute(sf::Vector2u{x, y});
  m_relativePosition = sf::Vector2u { x, y };
}

void GuiLayout::SetRelativePosition(const sf::Vector2u& position)
{
  m_position = ScaleRelativeToWindowAbsolute(position);
  m_relativePosition = position;
}

std::shared_ptr<GuiObject> GuiLayout::FindWidgetWithSmallestWidth()
{
  // if (m_widgets.size() > 0)
  // {
  //   auto max = std::max_element( m_widgets.begin(), m_widgets.end(),
  //                            []( std::shared_ptr<GuiObject> a, std::shared_ptr<GuiObject> b )
  //                            {
  //                                return a -> GetSize().width < b -> GetSize().width;
  //                            } ); 

  //   return m_widgets[std::distance(v.begin(), max)];
  // }
  // else
  // {
  //   std::cout << "[Warning][GuiLayout][FindWidgetWithSmallestWidth]: Couldn't find any widget.";
  //   return nullptr; 
  // }
  // if (m_widgets.size() != 0)
  // {
  //   float smallest = m_widgets.front() -> GetSize().width;

  //   for (const auto &widget : m_widgets)
  //   {
  //     smallest = widget -> GetSize().width < smallest ? widget -> GetSize().width : smallest;
  //     return widget;
  //   }

  //   return nullptr;
  // }
  // else
  // {
  //   std::cout << "[Warning][GuiLayout][FindWidgetWithSmallestWidth]: Couldn't find any widget.";
  //   return nullptr;
  // }

  return nullptr;
}

std::shared_ptr<GuiObject> GuiLayout::FindWidgetWithHighestWidth()
{
  // if (m_widgets.size() > 0)
  // {
  //   auto max = std::max_element( m_widgets.begin(), m_widgets.end(),
  //                            []( std::shared_ptr<GuiObject> a, std::shared_ptr<GuiObject> b )
  //                            {
  //                                return a -> GetSize().width < b -> GetSize().width;
  //                            } ); 

  //   return max;
  //   // float highest = m_widgets.front() -> GetSize().width;
  //   // std::shared_ptr<GuiObject> widestWidget;

  //   // for (auto widget : m_widgets)
  //   // {
  //   //   if (widget -> GetSize().width > highest)
  //   //   {
  //   //     highest = widget -> GetSize().width;
  //   //     widestWidget = widget;
  //   //   }
  //   // }

  //   // return widestWidget;
  // }
  // else
  // {
  //   std::cout << "[Warning][GuiLayout][FindWidgetWithSmallestWidth]: Couldn't find any widget.";
  //   return nullptr;
  // }

  return nullptr;
}

std::shared_ptr<GuiObject> GuiLayout::FindWidgetWithSmallestHeight()
{
  if (m_widgets.size() != 0)
  {
    float smallest = m_widgets.front() -> GetSize().height;

    for (const auto &widget : m_widgets)
    {
      smallest = widget -> GetSize().width < smallest ? widget -> GetSize().width : smallest;
      return widget;
    }

    return nullptr;
  }
  else
  {
    std::cout << "[Warning][GuiLayout][FindWidgetWithSmallestWidth]: Couldn't find any widget.";
    return nullptr;
  }
}

std::shared_ptr<GuiObject> GuiLayout::FindWidgetWithHighestHeight()
{
  if (m_widgets.size() != 0)
  {
    float highest = m_widgets.front() -> GetSize().height;

    for (const auto &widget : m_widgets)
    {
      highest = widget -> GetSize().width > highest ? widget -> GetSize().width : highest;
      return widget;
    }

    return nullptr;
  }
  else
  {
    std::cout << "[Warning][GuiLayout][FindWidgetWithSmallestWidth]: Couldn't find any widget.";
    return nullptr;
  }
}

const sf::Vector2f GuiLayout::ScaleRelativeToWindowAbsolute(const sf::Vector2u &proportions)
{
  if (m_window == nullptr)
  {
    throw std::logic_error("[Error][GuiLayout][ScaleRelativeToWindowAbsolute] Window is nullptr.");
  }

  if (proportions.x < 0 || proportions.x > 100 || proportions.y < 0 || proportions.y > 100)
  {
    throw std::logic_error("[Error][GuiLayout][ScaleRelativeToWindowAbsolute] x & y must be values between 0 and 100.");
  }
  
  const sf::Vector2f result = { (m_window -> GetWindowSize().x * static_cast<float>(proportions.x)) / 100, 
                                (m_window -> GetWindowSize().y * static_cast<float>(proportions.y)) / 100 };

  return result;
}

const sf::Vector2u GuiLayout::ScaleWindowAbsoluteToRelative(const sf::Vector2f &values)
{
  if (m_window == nullptr)
  {
    throw std::logic_error("[Error][GuiLayout][ScaleRelativeToWindowAbsolute] Window is nullptr.");
  }

  const sf::Vector2u result = { (100 * static_cast<unsigned int>(values.x) / m_window -> GetWindowSize().x), 
                                 (100 * static_cast<unsigned int>(values.y) / m_window -> GetWindowSize().y) };

  return result;
}
