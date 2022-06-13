#include <SFML/Graphics.hpp>

#include "gtest/gtest.h"

#include "GuiTextWidget.hpp"

TEST(GuiTextWidgetInitialPosition, BasicAssertions)
{
  GuiTextWidget gtw(nullptr);
  EXPECT_EQ(gtw.GetPosition(), sf::Vector2f(0, 0));
}