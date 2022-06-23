#include <iostream>
#include "gtest/gtest.h"
#include "wtypes.h"

#include "GuiLayout.hpp"
#include "GuiObject.hpp"
#include "Window.hpp"

class GuiLayoutFixture : public ::testing::Test {

 protected:

  GuiLayoutFixture()
  {
     window = new Window("Test");

     layout = std::make_shared<GuiLayout>(window);

     std::shared_ptr<GuiObject> o1 = std::make_shared<GuiObject>(nullptr);
     std::shared_ptr<GuiObject> o2 = std::make_shared<GuiObject>(nullptr);
     std::shared_ptr<GuiObject> o3 = std::make_shared<GuiObject>(nullptr);

     layout -> AddWidget(o1);
     layout -> AddWidget(o2);
     layout -> AddWidget(o3);
  }

  ~GuiLayoutFixture()
  {
     delete window;
  }

  void SetUp() override
  {
    RECT desktop;

    const HWND hDesktop = GetDesktopWindow();

    GetWindowRect(hDesktop, &desktop);

    x = desktop.right;
    y = desktop.bottom;
  }

protected:

  Window *window;
  std::shared_ptr<GuiLayout> layout;

  int x, y;

};

class Scaler : public GuiLayout
{

public:

  Scaler(Window *window) : GuiLayout(window) {}
  ~Scaler() = default;

  const sf::Vector2f GetScaledAbsoluteValue(const sf::Vector2u &v) { return ScaleRelativeToWindowAbsolute(v); }
  const sf::Vector2u GetScaledRelativeValue(const sf::Vector2f &v) { return ScaleWindowAbsoluteToRelative(v); }
};

TEST_F(GuiLayoutFixture, CheckScalingRelativeValuesToWindowAbsoluteResolution)
{
  Scaler s(window);

  EXPECT_EQ(s.GetScaledAbsoluteValue(sf::Vector2u(100, 100)), sf::Vector2f(x, y));
  EXPECT_EQ(s.GetScaledAbsoluteValue(sf::Vector2u(50, 50)),   sf::Vector2f(x / 2, y / 2));
}

TEST_F(GuiLayoutFixture, CheckScalingAbsoluteResolutionToRelativeValues)
{
  Scaler s(window);

  EXPECT_EQ(s.GetScaledRelativeValue(sf::Vector2f(1920, 1080)),   sf::Vector2u(100, 100));
  EXPECT_EQ(s.GetScaledRelativeValue(sf::Vector2f(x / 2, y / 2)), sf::Vector2u(50, 50));
}